//
//  Measurement.swift
//  GeoPen
//
//  Measurement model for core alpha and beta angles
//

import Foundation
import CoreLocation

struct Measurement: Identifiable, Codable {
    let id: UUID
    let timestamp: Date
    let alphaAngle: Double      // 0-90 degrees
    let betaAngle: Double       // 0-360 degrees
    let deviceId: String
    let operatorId: String?
    let coreSampleId: String?
    let projectId: String?
    let qualityScore: Double   // 0.0-1.0
    let location: Location?
    
    struct Location: Codable {
        let latitude: Double
        let longitude: Double
        let altitude: Double?
    }
    
    init(
        id: UUID = UUID(),
        timestamp: Date = Date(),
        alphaAngle: Double,
        betaAngle: Double,
        deviceId: String,
        operatorId: String? = nil,
        coreSampleId: String? = nil,
        projectId: String? = nil,
        qualityScore: Double = 1.0,
        location: Location? = nil
    ) {
        self.id = id
        self.timestamp = timestamp
        self.alphaAngle = alphaAngle
        self.betaAngle = betaAngle
        self.deviceId = deviceId
        self.operatorId = operatorId
        self.coreSampleId = coreSampleId
        self.projectId = projectId
        self.qualityScore = qualityScore
        self.location = location
    }
    
    // Validation
    var isValid: Bool {
        return alphaAngle >= 0 && alphaAngle <= 90 &&
               betaAngle >= 0 && betaAngle < 360 &&
               qualityScore >= 0 && qualityScore <= 1
    }
    
    // Formatted strings
    var alphaFormatted: String {
        return String(format: "%.1f°", alphaAngle)
    }
    
    var betaFormatted: String {
        return String(format: "%.1f°", betaAngle)
    }
    
    var timestampFormatted: String {
        let formatter = DateFormatter()
        formatter.dateStyle = .short
        formatter.timeStyle = .medium
        return formatter.string(from: timestamp)
    }
}

// CSV Export
extension Measurement {
    static func csvHeader() -> String {
        return "Timestamp,Alpha Angle,Beta Angle,Device ID,Operator ID,Core Sample ID,Project ID,Quality Score,Latitude,Longitude,Altitude"
    }
    
    func toCSV() -> String {
        let dateFormatter = ISO8601DateFormatter()
        let timestampStr = dateFormatter.string(from: timestamp)
        
        return String(format: "%@,%.2f,%.2f,%@,%@,%@,%@,%.2f,%.6f,%.6f,%@",
                      timestampStr,
                      alphaAngle,
                      betaAngle,
                      deviceId,
                      operatorId ?? "",
                      coreSampleId ?? "",
                      projectId ?? "",
                      qualityScore,
                      location?.latitude ?? 0.0,
                      location?.longitude ?? 0.0,
                      location?.altitude != nil ? String(format: "%.2f", location!.altitude!) : "")
    }
}

