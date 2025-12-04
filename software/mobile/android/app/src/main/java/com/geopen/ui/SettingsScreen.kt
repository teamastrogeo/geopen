package com.geopen.ui

import androidx.compose.foundation.layout.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Bluetooth
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import com.geopen.services.BLEManager

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun SettingsScreen(bleManager: BLEManager) {
    val isConnected by bleManager.isConnected.collectAsState()
    val discoveredDevices by bleManager.discoveredDevices.collectAsState()
    val isScanning by bleManager.isScanning.collectAsState()
    var showingDeviceList by remember { mutableStateOf(false) }
    
    Scaffold(
        topBar = {
            TopAppBar(
                title = { Text("Settings") }
            )
        }
    ) { padding ->
        Column(
            modifier = Modifier
                .fillMaxSize()
                .padding(padding)
        ) {
            // Device Section
            Card(
                modifier = Modifier
                    .fillMaxWidth()
                    .padding(16.dp)
            ) {
                Column(
                    modifier = Modifier.padding(16.dp),
                    verticalArrangement = Arrangement.spacedBy(12.dp)
                ) {
                    Text(
                        text = "Device",
                        style = MaterialTheme.typography.titleMedium
                    )
                    
                    Row(
                        modifier = Modifier.fillMaxWidth(),
                        horizontalArrangement = Arrangement.SpaceBetween
                    ) {
                        Text("Status")
                        Text(
                            text = if (isConnected) "Connected" else "Disconnected",
                            color = if (isConnected) 
                                MaterialTheme.colorScheme.primary 
                            else 
                                MaterialTheme.colorScheme.error
                        )
                    }
                    
                    Button(
                        onClick = {
                            if (isConnected) {
                                bleManager.disconnect()
                            } else {
                                showingDeviceList = true
                            }
                        },
                        modifier = Modifier.fillMaxWidth()
                    ) {
                        Text(if (isConnected) "Disconnect" else "Connect Device")
                    }
                }
            }
            
            // About Section
            Card(
                modifier = Modifier
                    .fillMaxWidth()
                    .padding(16.dp)
            ) {
                Column(
                    modifier = Modifier.padding(16.dp),
                    verticalArrangement = Arrangement.spacedBy(12.dp)
                ) {
                    Text(
                        text = "About",
                        style = MaterialTheme.typography.titleMedium
                    )
                    
                    Row(
                        modifier = Modifier.fillMaxWidth(),
                        horizontalArrangement = Arrangement.SpaceBetween
                    ) {
                        Text("Version")
                        Text("1.0.0", color = MaterialTheme.colorScheme.onSurfaceVariant)
                    }
                    
                    Row(
                        modifier = Modifier.fillMaxWidth(),
                        horizontalArrangement = Arrangement.SpaceBetween
                    ) {
                        Text("Build")
                        Text("1", color = MaterialTheme.colorScheme.onSurfaceVariant)
                    }
                }
            }
        }
        
        if (showingDeviceList) {
            DeviceListDialog(
                devices = discoveredDevices,
                isScanning = isScanning,
                onDeviceSelected = { device ->
                    bleManager.connect(device)
                    showingDeviceList = false
                },
                onDismiss = {
                    bleManager.stopScanning()
                    showingDeviceList = false
                },
                onStartScan = { bleManager.startScanning() }
            )
        }
    }
}

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun DeviceListDialog(
    devices: List<android.bluetooth.BluetoothDevice>,
    isScanning: Boolean,
    onDeviceSelected: (android.bluetooth.BluetoothDevice) -> Unit,
    onDismiss: () -> Unit,
    onStartScan: () -> Unit
) {
    AlertDialog(
        onDismissRequest = onDismiss,
        title = { Text("Select Device") },
        text = {
            Column {
                if (isScanning) {
                    LinearProgressIndicator(modifier = Modifier.fillMaxWidth())
                    Spacer(modifier = Modifier.height(8.dp))
                    Text("Scanning for devices...")
                } else if (devices.isEmpty) {
                    Text("No devices found")
                } else {
                    devices.forEach { device ->
                        TextButton(
                            onClick = { onDeviceSelected(device) },
                            modifier = Modifier.fillMaxWidth()
                        ) {
                            Column {
                                Text(device.name ?: "Unknown Device")
                                Text(
                                    text = device.address,
                                    style = MaterialTheme.typography.bodySmall
                                )
                            }
                        }
                    }
                }
            }
        },
        confirmButton = {
            TextButton(onClick = onStartScan) {
                Text("Scan")
            }
        },
        dismissButton = {
            TextButton(onClick = onDismiss) {
                Text("Cancel")
            }
        }
    )
}

