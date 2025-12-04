package com.geopen.services

import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothGatt
import android.bluetooth.BluetoothGattCallback
import android.bluetooth.BluetoothGattCharacteristic
import android.bluetooth.BluetoothManager
import android.bluetooth.BluetoothProfile
import android.bluetooth.le.BluetoothLeScanner
import android.bluetooth.le.ScanCallback
import android.bluetooth.le.ScanFilter
import android.bluetooth.le.ScanResult
import android.bluetooth.le.ScanSettings
import android.content.Context
import android.os.ParcelUuid
import com.geopen.models.Measurement
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import java.util.UUID

class BLEManager(private val context: Context) {
    companion object {
        private const val MEASUREMENT_SERVICE_UUID = "12345678-1234-1234-1234-123456789ABC"
        private const val MEASUREMENT_CHARACTERISTIC_UUID = "12345678-1234-1234-1234-123456789ABD"
        
        @Volatile
        private var INSTANCE: BLEManager? = null
        
        fun getInstance(context: Context): BLEManager {
            return INSTANCE ?: synchronized(this) {
                INSTANCE ?: BLEManager(context.applicationContext).also { INSTANCE = it }
            }
        }
    }
    
    private val bluetoothManager: BluetoothManager =
        context.getSystemService(Context.BLUETOOTH_SERVICE) as BluetoothManager
    private val bluetoothAdapter: BluetoothAdapter? = bluetoothManager.adapter
    private val bluetoothLeScanner: BluetoothLeScanner? = bluetoothAdapter?.bluetoothLeScanner
    
    private var connectedGatt: BluetoothGatt? = null
    private var measurementCharacteristic: BluetoothGattCharacteristic? = null
    
    // State flows
    val isScanning = MutableStateFlow(false)
    val isConnected = MutableStateFlow(false)
    val discoveredDevices = MutableStateFlow<List<BluetoothDevice>>(emptyList())
    val currentMeasurement = MutableStateFlow<Measurement?>(null)
    val connectionStatus = MutableStateFlow("Disconnected")
    
    private val scanCallback = object : ScanCallback() {
        override fun onScanResult(callbackType: Int, result: ScanResult) {
            val device = result.device
            val currentList = discoveredDevices.value
            if (!currentList.contains(device)) {
                discoveredDevices.value = currentList + device
            }
        }
        
        override fun onScanFailed(errorCode: Int) {
            connectionStatus.value = "Scan failed: $errorCode"
            isScanning.value = false
        }
    }
    
    private val gattCallback = object : BluetoothGattCallback() {
        override fun onConnectionStateChange(gatt: BluetoothGatt, status: Int, newState: Int) {
            when (newState) {
                BluetoothProfile.STATE_CONNECTED -> {
                    isConnected.value = true
                    connectionStatus.value = "Connected"
                    gatt.discoverServices()
                }
                BluetoothProfile.STATE_DISCONNECTED -> {
                    isConnected.value = false
                    connectionStatus.value = "Disconnected"
                    connectedGatt = null
                    measurementCharacteristic = null
                }
            }
        }
        
        override fun onServicesDiscovered(gatt: BluetoothGatt, status: Int) {
            if (status == BluetoothGatt.GATT_SUCCESS) {
                val service = gatt.getService(UUID.fromString(MEASUREMENT_SERVICE_UUID))
                service?.let {
                    measurementCharacteristic = it.getCharacteristic(
                        UUID.fromString(MEASUREMENT_CHARACTERISTIC_UUID)
                    )
                    measurementCharacteristic?.let { char ->
                        gatt.setCharacteristicNotification(char, true)
                    }
                }
            }
        }
        
        override fun onCharacteristicChanged(
            gatt: BluetoothGatt,
            characteristic: BluetoothGattCharacteristic
        ) {
            if (characteristic.uuid == UUID.fromString(MEASUREMENT_CHARACTERISTIC_UUID)) {
                parseMeasurementData(characteristic.value)
            }
        }
    }
    
    fun startScanning() {
        if (bluetoothAdapter?.isEnabled != true) {
            connectionStatus.value = "Bluetooth not enabled"
            return
        }
        
        isScanning.value = true
        discoveredDevices.value = emptyList()
        
        val filter = ScanFilter.Builder()
            .setServiceUuid(ParcelUuid(UUID.fromString(MEASUREMENT_SERVICE_UUID)))
            .build()
        
        val settings = ScanSettings.Builder()
            .setScanMode(ScanSettings.SCAN_MODE_LOW_LATENCY)
            .build()
        
        bluetoothLeScanner?.startScan(listOf(filter), settings, scanCallback)
        connectionStatus.value = "Scanning for devices..."
    }
    
    fun stopScanning() {
        bluetoothLeScanner?.stopScan(scanCallback)
        isScanning.value = false
    }
    
    fun connect(device: BluetoothDevice) {
        stopScanning()
        connectedGatt = device.connectGatt(context, false, gattCallback)
        connectionStatus.value = "Connecting..."
    }
    
    fun disconnect() {
        connectedGatt?.disconnect()
        connectedGatt?.close()
        connectedGatt = null
    }
    
    fun triggerMeasurement() {
        val characteristic = measurementCharacteristic ?: return
        val command = byteArrayOf(0x01) // Trigger command
        characteristic.value = command
        connectedGatt?.writeCharacteristic(characteristic)
    }
    
    private fun parseMeasurementData(data: ByteArray) {
        if (data.size < 16) return
        
        val alpha = data.sliceArray(0..3).let { 
            java.nio.ByteBuffer.wrap(it).order(java.nio.ByteOrder.LITTLE_ENDIAN).float
        }
        val beta = data.sliceArray(4..7).let {
            java.nio.ByteBuffer.wrap(it).order(java.nio.ByteOrder.LITTLE_ENDIAN).float
        }
        val quality = data.sliceArray(8..11).let {
            java.nio.ByteBuffer.wrap(it).order(java.nio.ByteOrder.LITTLE_ENDIAN).float
        }
        
        val measurement = Measurement(
            alphaAngle = alpha.toDouble(),
            betaAngle = beta.toDouble(),
            deviceId = connectedGatt?.device?.address ?: "unknown",
            qualityScore = quality.toDouble()
        )
        
        currentMeasurement.value = measurement
    }
}

