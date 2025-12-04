//
//  Constants.swift
//  GeoPen
//
//  App-wide constants
//

import Foundation
import CoreBluetooth

struct GeoPenConstants {
    // BLE Service UUIDs
    static let measurementServiceUUID = CBUUID(string: "12345678-1234-1234-1234-123456789ABC")
    static let measurementCharacteristicUUID = CBUUID(string: "12345678-1234-1234-1234-123456789ABD")
    static let deviceInfoServiceUUID = CBUUID(string: "0000180A-0000-1000-8000-00805F9B34FB")
    
    // Measurement constants
    static let minAlphaAngle: Double = 0.0
    static let maxAlphaAngle: Double = 90.0
    static let minBetaAngle: Double = 0.0
    static let maxBetaAngle: Double = 360.0
    
    // UI Constants
    static let measurementUpdateInterval: TimeInterval = 0.1 // 100ms
    static let connectionTimeout: TimeInterval = 10.0 // 10 seconds
}

