//
//  GeoPenApp.swift
//  GeoPen
//
//  Main app entry point
//

import SwiftUI

@main
struct GeoPenApp: App {
    @StateObject private var dataManager = DataManager.shared
    @StateObject private var bleManager = BLEManager.shared
    
    var body: some Scene {
        WindowGroup {
            ContentView()
                .environmentObject(bleManager)
                .environmentObject(dataManager)
        }
    }
}

