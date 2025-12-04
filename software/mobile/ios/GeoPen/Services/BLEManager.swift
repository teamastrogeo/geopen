//
//  BLEManager.swift
//  GeoPen
//
//  Bluetooth Low Energy manager for GeoPen device communication
//

import Foundation
import CoreBluetooth
import Combine

class BLEManager: NSObject, ObservableObject {
    static let shared = BLEManager()
    
    // Published properties
    @Published var isScanning = false
    @Published var isConnected = false
    @Published var discoveredDevices: [CBPeripheral] = []
    @Published var currentMeasurement: Measurement?
    @Published var connectionStatus: String = "Disconnected"
    
    // BLE properties
    private var centralManager: CBCentralManager!
    private var connectedPeripheral: CBPeripheral?
    private var measurementCharacteristic: CBCharacteristic?
    
    // Service and characteristic UUIDs
    private let serviceUUID = CBUUID(string: "0000180A-0000-1000-8000-00805F9B34FB") // Device Information
    private let measurementServiceUUID = CBUUID(string: "12345678-1234-1234-1234-123456789ABC") // Custom Measurement Service
    private let measurementCharacteristicUUID = CBUUID(string: "12345678-1234-1234-1234-123456789ABD")
    
    override init() {
        super.init()
        centralManager = CBCentralManager(delegate: self, queue: nil)
    }
    
    // MARK: - Public Methods
    
    func startScanning() {
        guard centralManager.state == .poweredOn else {
            connectionStatus = "Bluetooth not available"
            return
        }
        
        isScanning = true
        discoveredDevices.removeAll()
        centralManager.scanForPeripherals(withServices: [measurementServiceUUID], options: nil)
        connectionStatus = "Scanning for devices..."
    }
    
    func stopScanning() {
        centralManager.stopScan()
        isScanning = false
    }
    
    func connect(to peripheral: CBPeripheral) {
        stopScanning()
        connectedPeripheral = peripheral
        centralManager.connect(peripheral, options: nil)
        connectionStatus = "Connecting..."
    }
    
    func disconnect() {
        if let peripheral = connectedPeripheral {
            centralManager.cancelPeripheralConnection(peripheral)
        }
    }
    
    func triggerMeasurement() {
        guard let peripheral = connectedPeripheral,
              let characteristic = measurementCharacteristic else {
            return
        }
        
        // Send trigger command (implementation depends on BLE protocol)
        let command: [UInt8] = [0x01] // Example trigger command
        let data = Data(command)
        peripheral.writeValue(data, for: characteristic, type: .withResponse)
    }
}

// MARK: - CBCentralManagerDelegate

extension BLEManager: CBCentralManagerDelegate {
    func centralManagerDidUpdateState(_ central: CBCentralManager) {
        switch central.state {
        case .poweredOn:
            connectionStatus = "Ready"
        case .poweredOff:
            connectionStatus = "Bluetooth is off"
            isConnected = false
        case .unauthorized:
            connectionStatus = "Bluetooth unauthorized"
        case .unsupported:
            connectionStatus = "Bluetooth not supported"
        default:
            break
        }
    }
    
    func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber) {
        if !discoveredDevices.contains(peripheral) {
            discoveredDevices.append(peripheral)
        }
    }
    
    func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {
        isConnected = true
        connectionStatus = "Connected"
        peripheral.delegate = self
        peripheral.discoverServices([measurementServiceUUID, serviceUUID])
    }
    
    func centralManager(_ central: CBCentralManager, didDisconnectPeripheral peripheral: CBPeripheral, error: Error?) {
        isConnected = false
        connectionStatus = "Disconnected"
        connectedPeripheral = nil
        measurementCharacteristic = nil
    }
    
    func centralManager(_ central: CBCentralManager, didFailToConnect peripheral: CBPeripheral, error: Error?) {
        connectionStatus = "Connection failed: \(error?.localizedDescription ?? "Unknown error")"
    }
}

// MARK: - CBPeripheralDelegate

extension BLEManager: CBPeripheralDelegate {
    func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
        guard let services = peripheral.services else { return }
        
        for service in services {
            peripheral.discoverCharacteristics(nil, for: service)
        }
    }
    
    func peripheral(_ peripheral: CBPeripheral, didDiscoverCharacteristicsFor service: CBService, error: Error?) {
        guard let characteristics = service.characteristics else { return }
        
        for characteristic in characteristics {
            if characteristic.uuid == measurementCharacteristicUUID {
                measurementCharacteristic = characteristic
                peripheral.setNotifyValue(true, for: characteristic)
            }
        }
    }
    
    func peripheral(_ peripheral: CBPeripheral, didUpdateValueFor characteristic: CBCharacteristic, error: Error?) {
        guard let data = characteristic.value else { return }
        
        if characteristic.uuid == measurementCharacteristicUUID {
            parseMeasurementData(data)
        }
    }
    
    private func parseMeasurementData(_ data: Data) {
        // Parse measurement data from BLE packet
        // Format: [alpha (float), beta (float), quality (float), timestamp (uint32)]
        guard data.count >= 16 else { return }
        
        let alpha = data.withUnsafeBytes { $0.load(fromByteOffset: 0, as: Float.self) }
        let beta = data.withUnsafeBytes { $0.load(fromByteOffset: 4, as: Float.self) }
        let quality = data.withUnsafeBytes { $0.load(fromByteOffset: 8, as: Float.self) }
        let timestamp = data.withUnsafeBytes { $0.load(fromByteOffset: 12, as: UInt32.self) }
        
        let measurement = Measurement(
            alphaAngle: Double(alpha),
            betaAngle: Double(beta),
            deviceId: connectedPeripheral?.identifier.uuidString ?? "unknown",
            qualityScore: Double(quality)
        )
        
        DispatchQueue.main.async {
            self.currentMeasurement = measurement
        }
    }
}

