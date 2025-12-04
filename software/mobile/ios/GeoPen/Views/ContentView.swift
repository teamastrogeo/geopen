//
//  ContentView.swift
//  GeoPen
//
//  Main content view with tab navigation
//

import SwiftUI

struct ContentView: View {
    @StateObject private var bleManager = BLEManager.shared
    @State private var selectedTab = 0
    
    var body: some View {
        TabView(selection: $selectedTab) {
            MeasurementView()
                .tabItem {
                    Label("Measure", systemImage: "ruler")
                }
                .tag(0)
            
            HistoryView()
                .tabItem {
                    Label("History", systemImage: "list.bullet")
                }
                .tag(1)
            
            SettingsView()
                .tabItem {
                    Label("Settings", systemImage: "gearshape")
                }
                .tag(2)
        }
    }
}

#Preview {
    ContentView()
}

