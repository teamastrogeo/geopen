//
//  SettingsView.swift
//  GeoPen
//
//  Settings and configuration view
//

import SwiftUI

struct SettingsView: View {
    @EnvironmentObject var bleManager: BLEManager
    @State private var showingDeviceList = false
    
    var body: some View {
        NavigationView {
            List {
                // Device Connection Section
                Section(header: Text("Device")) {
                    HStack {
                        Text("Status")
                        Spacer()
                        Text(bleManager.isConnected ? "Connected" : "Disconnected")
                            .foregroundColor(bleManager.isConnected ? .green : .red)
                    }
                    
                    Button(action: {
                        if bleManager.isConnected {
                            bleManager.disconnect()
                        } else {
                            showingDeviceList = true
                        }
                    }) {
                        HStack {
                            Text(bleManager.isConnected ? "Disconnect" : "Connect Device")
                            Spacer()
                            Image(systemName: "chevron.right")
                                .foregroundColor(.gray)
                        }
                    }
                }
                
                // App Information Section
                Section(header: Text("About")) {
                    HStack {
                        Text("Version")
                        Spacer()
                        Text("1.0.0")
                            .foregroundColor(.secondary)
                    }
                    
                    HStack {
                        Text("Build")
                        Spacer()
                        Text("1")
                            .foregroundColor(.secondary)
                    }
                }
                
                // Data Section
                Section(header: Text("Data")) {
                    NavigationLink(destination: CalibrationView()) {
                        HStack {
                            Image(systemName: "ruler")
                            Text("Calibration")
                        }
                    }
                }
            }
            .navigationTitle("Settings")
            .sheet(isPresented: $showingDeviceList) {
                DeviceListView()
            }
        }
    }
}

struct DeviceListView: View {
    @EnvironmentObject var bleManager: BLEManager
    @Environment(\.dismiss) var dismiss
    
    var body: some View {
        NavigationView {
            List {
                if bleManager.isScanning {
                    HStack {
                        ProgressView()
                        Text("Scanning for devices...")
                    }
                } else if bleManager.discoveredDevices.isEmpty {
                    Text("No devices found")
                        .foregroundColor(.secondary)
                } else {
                    ForEach(bleManager.discoveredDevices, id: \.identifier) { device in
                        Button(action: {
                            bleManager.connect(to: device)
                            dismiss()
                        }) {
                            VStack(alignment: .leading) {
                                Text(device.name ?? "Unknown Device")
                                    .font(.headline)
                                Text(device.identifier.uuidString)
                                    .font(.caption)
                                    .foregroundColor(.secondary)
                            }
                        }
                    }
                }
            }
            .navigationTitle("Select Device")
            .navigationBarTitleDisplayMode(.inline)
            .toolbar {
                ToolbarItem(placement: .navigationBarLeading) {
                    Button("Cancel") {
                        bleManager.stopScanning()
                        dismiss()
                    }
                }
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button("Scan") {
                        bleManager.startScanning()
                    }
                }
            }
            .onAppear {
                bleManager.startScanning()
            }
            .onDisappear {
                bleManager.stopScanning()
            }
        }
    }
}

struct CalibrationView: View {
    var body: some View {
        VStack(spacing: 20) {
            Text("Calibration Assistant")
                .font(.headline)
            
            Text("Follow these steps to calibrate your GeoPen device:")
                .font(.subheadline)
                .foregroundColor(.secondary)
                .multilineTextAlignment(.center)
            
            VStack(alignment: .leading, spacing: 15) {
                CalibrationStep(number: 1, text: "Place device on flat surface")
                CalibrationStep(number: 2, text: "Press and hold calibration button")
                CalibrationStep(number: 3, text: "Wait for confirmation")
            }
            .padding()
            
            Button(action: {}) {
                Text("Start Calibration")
                    .font(.headline)
                    .foregroundColor(.white)
                    .frame(maxWidth: .infinity)
                    .padding()
                    .background(Color.blue)
                    .cornerRadius(12)
            }
            .padding()
            
            Spacer()
        }
        .padding()
        .navigationTitle("Calibration")
        .navigationBarTitleDisplayMode(.inline)
    }
}

struct CalibrationStep: View {
    let number: Int
    let text: String
    
    var body: some View {
        HStack {
            Text("\(number)")
                .font(.headline)
                .foregroundColor(.white)
                .frame(width: 30, height: 30)
                .background(Color.blue)
                .clipShape(Circle())
            
            Text(text)
                .font(.body)
        }
    }
}

#Preview {
    SettingsView()
        .environmentObject(BLEManager.shared)
}

