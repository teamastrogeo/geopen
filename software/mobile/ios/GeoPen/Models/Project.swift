//
//  Project.swift
//  GeoPen
//
//  Project model for organizing measurements
//

import Foundation

struct Project: Identifiable, Codable {
    let id: UUID
    let name: String
    let description: String?
    let createdAt: Date
    var measurements: [UUID] // Measurement IDs
    
    init(id: UUID = UUID(), name: String, description: String? = nil) {
        self.id = id
        self.name = name
        self.description = description
        self.createdAt = Date()
        self.measurements = []
    }
}

