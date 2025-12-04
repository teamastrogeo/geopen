//
//  HistoryView.swift
//  GeoPen
//
//  Measurement history view
//

import SwiftUI

struct HistoryView: View {
    @EnvironmentObject var dataManager: DataManager
    @State private var searchText = ""
    @State private var showingExportSheet = false
    
    var filteredMeasurements: [Measurement] {
        if searchText.isEmpty {
            return dataManager.measurements
        }
        return dataManager.measurements.filter { measurement in
            measurement.coreSampleId?.localizedCaseInsensitiveContains(searchText) ?? false ||
            measurement.projectId?.localizedCaseInsensitiveContains(searchText) ?? false ||
            measurement.operatorId?.localizedCaseInsensitiveContains(searchText) ?? false
        }
    }
    
    var body: some View {
        NavigationView {
            VStack {
                if filteredMeasurements.isEmpty {
                    EmptyHistoryView()
                } else {
                    List {
                        ForEach(filteredMeasurements) { measurement in
                            MeasurementRowView(measurement: measurement)
                        }
                        .onDelete(perform: deleteMeasurements)
                    }
                    .searchable(text: $searchText, prompt: "Search measurements")
                }
            }
            .navigationTitle("History")
            .toolbar {
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button(action: { showingExportSheet = true }) {
                        Image(systemName: "square.and.arrow.up")
                    }
                }
            }
            .sheet(isPresented: $showingExportSheet) {
                ExportSheet(measurements: filteredMeasurements)
            }
        }
    }
    
    private func deleteMeasurements(at offsets: IndexSet) {
        for index in offsets {
            dataManager.deleteMeasurement(filteredMeasurements[index])
        }
    }
}

struct MeasurementRowView: View {
    let measurement: Measurement
    
    var body: some View {
        VStack(alignment: .leading, spacing: 8) {
            HStack {
                VStack(alignment: .leading) {
                    Text("α: \(measurement.alphaFormatted)  β: \(measurement.betaFormatted)")
                        .font(.headline)
                    
                    if let coreSampleId = measurement.coreSampleId {
                        Text("Core: \(coreSampleId)")
                            .font(.subheadline)
                            .foregroundColor(.secondary)
                    }
                    
                    if let projectId = measurement.projectId {
                        Text("Project: \(projectId)")
                            .font(.subheadline)
                            .foregroundColor(.secondary)
                    }
                }
                
                Spacer()
                
                VStack(alignment: .trailing) {
                    Text(measurement.timestampFormatted)
                        .font(.caption)
                        .foregroundColor(.secondary)
                    
                    Text(String(format: "%.0f%%", measurement.qualityScore * 100))
                        .font(.caption)
                        .foregroundColor(measurement.qualityScore > 0.8 ? .green : .orange)
                }
            }
        }
        .padding(.vertical, 4)
    }
}

struct EmptyHistoryView: View {
    var body: some View {
        VStack(spacing: 20) {
            Image(systemName: "list.bullet")
                .font(.system(size: 64))
                .foregroundColor(.gray)
            Text("No measurements yet")
                .font(.headline)
                .foregroundColor(.secondary)
            Text("Start measuring to see history here")
                .font(.subheadline)
                .foregroundColor(.secondary)
        }
    }
}

struct ExportSheet: View {
    let measurements: [Measurement]
    @Environment(\.dismiss) var dismiss
    @State private var exportFormat: ExportFormat = .csv
    
    enum ExportFormat {
        case csv, json
    }
    
    var body: some View {
        NavigationView {
            VStack(spacing: 20) {
                Picker("Format", selection: $exportFormat) {
                    Text("CSV").tag(ExportFormat.csv)
                    Text("JSON").tag(ExportFormat.json)
                }
                .pickerStyle(SegmentedPickerStyle())
                .padding()
                
                Button(action: exportData) {
                    Text("Export")
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
            .navigationTitle("Export Data")
            .navigationBarTitleDisplayMode(.inline)
            .toolbar {
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button("Done") {
                        dismiss()
                    }
                }
            }
        }
    }
    
    private func exportData() {
        let exportString: String
        switch exportFormat {
        case .csv:
            exportString = exportToCSV()
        case .json:
            exportString = exportToJSON()
        }
        
        // Share sheet implementation
        let activityVC = UIActivityViewController(
            activityItems: [exportString],
            applicationActivities: nil
        )
        
        if let windowScene = UIApplication.shared.connectedScenes.first as? UIWindowScene,
           let rootViewController = windowScene.windows.first?.rootViewController {
            rootViewController.present(activityVC, animated: true)
        }
        
        dismiss()
    }
    
    private func exportToCSV() -> String {
        var csv = Measurement.csvHeader() + "\n"
        csv += measurements.map { $0.toCSV() }.joined(separator: "\n")
        return csv
    }
    
    private func exportToJSON() -> String {
        let encoder = JSONEncoder()
        encoder.dateEncodingStrategy = .iso8601
        encoder.outputFormatting = .prettyPrinted
        
        if let data = try? encoder.encode(measurements),
           let jsonString = String(data: data, encoding: .utf8) {
            return jsonString
        }
        return "[]"
    }
}

#Preview {
    HistoryView()
        .environmentObject(DataManager.shared)
}

