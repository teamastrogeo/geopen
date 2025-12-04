package com.geopen.models

import java.text.SimpleDateFormat
import java.util.*

/**
 * Measurement model for core alpha and beta angles
 */
data class Measurement(
    val id: UUID = UUID.randomUUID(),
    val timestamp: Date = Date(),
    val alphaAngle: Double,      // 0-90 degrees
    val betaAngle: Double,       // 0-360 degrees
    val deviceId: String,
    val operatorId: String? = null,
    val coreSampleId: String? = null,
    val projectId: String? = null,
    val qualityScore: Double = 1.0,  // 0.0-1.0
    val location: Location? = null
) {
    data class Location(
        val latitude: Double,
        val longitude: Double,
        val altitude: Double? = null
    )
    
    /**
     * Validate measurement data
     */
    fun isValid(): Boolean {
        return alphaAngle in 0.0..90.0 &&
               betaAngle in 0.0..360.0 &&
               qualityScore in 0.0..1.0
    }
    
    /**
     * Format alpha angle as string
     */
    fun alphaFormatted(): String = "%.1f°".format(alphaAngle)
    
    /**
     * Format beta angle as string
     */
    fun betaFormatted(): String = "%.1f°".format(betaAngle)
    
    /**
     * Format timestamp as string
     */
    fun timestampFormatted(): String {
        val formatter = SimpleDateFormat("MMM dd, yyyy HH:mm", Locale.getDefault())
        return formatter.format(timestamp)
    }
    
    /**
     * Convert to CSV format
     */
    fun toCSV(): String {
        val timestampStr = SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss.SSS'Z'", Locale.US).format(timestamp)
        return "$timestampStr,$alphaAngle,$betaAngle,$deviceId,${operatorId ?: ""},${coreSampleId ?: ""},${projectId ?: ""},$qualityScore,${location?.latitude ?: 0.0},${location?.longitude ?: 0.0},${location?.altitude ?: ""}"
    }
    
    companion object {
        /**
         * CSV header row
         */
        fun csvHeader(): String {
            return "Timestamp,Alpha Angle,Beta Angle,Device ID,Operator ID,Core Sample ID,Project ID,Quality Score,Latitude,Longitude,Altitude"
        }
    }
}
