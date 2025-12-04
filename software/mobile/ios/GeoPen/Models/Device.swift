//
//  Device.swift
//  GeoPen
//
//  Device model for GeoPen hardware
//

import Foundation
import CoreBluetooth

struct Device: Identifiable {
    let id: UUID
    let name: String
    let peripheral: CBPeripheral
    let rssi: Int
    
    init(peripheral: CBPeripheral, rssi: Int) {
        self.id = peripheral.identifier
        self.name = peripheral.name ?? "Unknown Device"
        self.peripheral = peripheral
        self.rssi = rssi
    }
}

