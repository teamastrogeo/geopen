//
//  DataManager.swift
//  GeoPen
//
//  Data persistence manager using UserDefaults (simple implementation)
//  In production, use Core Data or SQLite
//

import Foundation
import Combine

class DataManager: ObservableObject {
    static let shared = DataManager()
    
    @Published var measurements: [Measurement] = []
    
    private let measurementsKey = "GeoPenMeasurements"
    
    private init() {
        loadMeasurements()
    }
    
    func saveMeasurement(_ measurement: Measurement) {
        measurements.append(measurement)
        saveMeasurements()
    }
    
    func deleteMeasurement(_ measurement: Measurement) {
        measurements.removeAll { $0.id == measurement.id }
        saveMeasurements()
    }
    
    func deleteAllMeasurements() {
        measurements.removeAll()
        saveMeasurements()
    }
    
    private func saveMeasurements() {
        if let encoded = try? JSONEncoder().encode(measurements) {
            UserDefaults.standard.set(encoded, forKey: measurementsKey)
        }
    }
    
    private func loadMeasurements() {
        if let data = UserDefaults.standard.data(forKey: measurementsKey),
           let decoded = try? JSONDecoder().decode([Measurement].self, from: data) {
            measurements = decoded
        }
    }
    
    func exportToCSV() -> String {
        var csv = Measurement.csvHeader() + "\n"
        csv += measurements.map { $0.toCSV() }.joined(separator: "\n")
        return csv
    }
    
    func exportToJSON() -> String {
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

