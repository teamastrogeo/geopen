//
//  MeasurementView.swift
//  GeoPen
//
//  Real-time measurement display view
//

import SwiftUI

struct MeasurementView: View {
    @EnvironmentObject var bleManager: BLEManager
    @EnvironmentObject var dataManager: DataManager
    @State private var currentMeasurement: Measurement?
    @State private var isRecording = false
    @State private var operatorId: String = ""
    @State private var coreSampleId: String = ""
    @State private var projectId: String = ""
    
    var body: some View {
        NavigationView {
            VStack(spacing: 30) {
                // Connection Status
                ConnectionStatusView()
                
                // Measurement Display
                if let measurement = currentMeasurement ?? bleManager.currentMeasurement {
                    MeasurementDisplayView(measurement: measurement)
                } else {
                    PlaceholderMeasurementView()
                }
                
                // Controls
                VStack(spacing: 20) {
                    // Trigger Measurement Button
                    Button(action: triggerMeasurement) {
                        HStack {
                            Image(systemName: "ruler.fill")
                            Text("Measure")
                        }
                        .font(.headline)
                        .foregroundColor(.white)
                        .frame(maxWidth: .infinity)
                        .padding()
                        .background(bleManager.isConnected ? Color.blue : Color.gray)
                        .cornerRadius(12)
                    }
                    .disabled(!bleManager.isConnected)
                    
                    // Save Measurement Button
                    if let measurement = currentMeasurement ?? bleManager.currentMeasurement {
                        Button(action: saveMeasurement) {
                            HStack {
                                Image(systemName: "square.and.arrow.down")
                                Text("Save Measurement")
                            }
                            .font(.headline)
                            .foregroundColor(.white)
                            .frame(maxWidth: .infinity)
                            .padding()
                            .background(Color.green)
                            .cornerRadius(12)
                        }
                    }
                }
                .padding(.horizontal)
                
                // Metadata Input
                MeasurementMetadataView(
                    operatorId: $operatorId,
                    coreSampleId: $coreSampleId,
                    projectId: $projectId
                )
                
                Spacer()
            }
            .padding()
            .navigationTitle("GeoPen")
            .onChange(of: bleManager.currentMeasurement) { newValue in
                currentMeasurement = newValue
            }
        }
    }
    
    private func triggerMeasurement() {
        bleManager.triggerMeasurement()
    }
    
    private func saveMeasurement() {
        guard let measurement = currentMeasurement ?? bleManager.currentMeasurement else {
            return
        }
        
        var savedMeasurement = measurement
        if !operatorId.isEmpty {
            savedMeasurement = Measurement(
                id: measurement.id,
                timestamp: measurement.timestamp,
                alphaAngle: measurement.alphaAngle,
                betaAngle: measurement.betaAngle,
                deviceId: measurement.deviceId,
                operatorId: operatorId.isEmpty ? nil : operatorId,
                coreSampleId: coreSampleId.isEmpty ? nil : coreSampleId,
                projectId: projectId.isEmpty ? nil : projectId,
                qualityScore: measurement.qualityScore,
                location: measurement.location
            )
        }
        
        dataManager.saveMeasurement(savedMeasurement)
        
        // Clear metadata
        operatorId = ""
        coreSampleId = ""
        projectId = ""
        currentMeasurement = nil
    }
}

struct ConnectionStatusView: View {
    @EnvironmentObject var bleManager: BLEManager
    
    var body: some View {
        HStack {
            Circle()
                .fill(bleManager.isConnected ? Color.green : Color.red)
                .frame(width: 12, height: 12)
            Text(bleManager.connectionStatus)
                .font(.subheadline)
                .foregroundColor(.secondary)
        }
        .padding()
        .background(Color(.systemGray6))
        .cornerRadius(8)
    }
}

struct MeasurementDisplayView: View {
    let measurement: Measurement
    
    var body: some View {
        VStack(spacing: 30) {
            // Alpha Angle
            VStack(spacing: 10) {
                Text("Alpha Angle")
                    .font(.headline)
                    .foregroundColor(.secondary)
                Text(measurement.alphaFormatted)
                    .font(.system(size: 64, weight: .bold))
                    .foregroundColor(.blue)
                Text("α")
                    .font(.title2)
                    .foregroundColor(.secondary)
            }
            
            Divider()
            
            // Beta Angle
            VStack(spacing: 10) {
                Text("Beta Angle")
                    .font(.headline)
                    .foregroundColor(.secondary)
                Text(measurement.betaFormatted)
                    .font(.system(size: 64, weight: .bold))
                    .foregroundColor(.green)
                Text("β")
                    .font(.title2)
                    .foregroundColor(.secondary)
            }
            
            // Quality Score
            HStack {
                Text("Quality:")
                    .font(.subheadline)
                    .foregroundColor(.secondary)
                Text(String(format: "%.1f%%", measurement.qualityScore * 100))
                    .font(.subheadline)
                    .fontWeight(.semibold)
            }
            .padding(.top)
        }
        .padding()
        .frame(maxWidth: .infinity)
        .background(Color(.systemGray6))
        .cornerRadius(16)
    }
}

struct PlaceholderMeasurementView: View {
    var body: some View {
        VStack(spacing: 20) {
            Image(systemName: "ruler")
                .font(.system(size: 64))
                .foregroundColor(.gray)
            Text("No measurement")
                .font(.headline)
                .foregroundColor(.secondary)
            Text("Connect device and press Measure")
                .font(.subheadline)
                .foregroundColor(.secondary)
        }
        .padding()
        .frame(maxWidth: .infinity)
        .frame(height: 300)
        .background(Color(.systemGray6))
        .cornerRadius(16)
    }
}

struct MeasurementMetadataView: View {
    @Binding var operatorId: String
    @Binding var coreSampleId: String
    @Binding var projectId: String
    
    var body: some View {
        VStack(alignment: .leading, spacing: 15) {
            Text("Measurement Metadata")
                .font(.headline)
            
            TextField("Operator ID", text: $operatorId)
                .textFieldStyle(RoundedBorderTextFieldStyle())
            
            TextField("Core Sample ID", text: $coreSampleId)
                .textFieldStyle(RoundedBorderTextFieldStyle())
            
            TextField("Project ID", text: $projectId)
                .textFieldStyle(RoundedBorderTextFieldStyle())
        }
        .padding()
        .background(Color(.systemGray6))
        .cornerRadius(12)
    }
}

#Preview {
    MeasurementView()
        .environmentObject(BLEManager.shared)
        .environmentObject(DataManager.shared)
}

