package com.geopen.services

import android.content.Context
import android.content.SharedPreferences
import com.geopen.models.Measurement
import com.google.gson.Gson
import com.google.gson.reflect.TypeToken
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow

class DataManager private constructor(context: Context) {
    companion object {
        private const val PREFS_NAME = "GeoPenPrefs"
        private const val KEY_MEASUREMENTS = "measurements"
        
        @Volatile
        private var INSTANCE: DataManager? = null
        
        fun getInstance(context: Context? = null): DataManager {
            return INSTANCE ?: synchronized(this) {
                INSTANCE ?: DataManager(
                    context ?: throw IllegalArgumentException("Context required for first initialization")
                ).also { INSTANCE = it }
            }
        }
    }
    
    private val prefs: SharedPreferences = context.getSharedPreferences(PREFS_NAME, Context.MODE_PRIVATE)
    private val gson = Gson()
    
    private val _measurements = MutableStateFlow<List<Measurement>>(loadMeasurements())
    val measurements: StateFlow<List<Measurement>> = _measurements.asStateFlow()
    
    private fun loadMeasurements(): List<Measurement> {
        val json = prefs.getString(KEY_MEASUREMENTS, null) ?: return emptyList()
        val type = object : TypeToken<List<Measurement>>() {}.type
        return gson.fromJson(json, type) ?: emptyList()
    }
    
    private fun saveMeasurements() {
        val json = gson.toJson(_measurements.value)
        prefs.edit().putString(KEY_MEASUREMENTS, json).apply()
    }
    
    fun saveMeasurement(measurement: Measurement) {
        _measurements.value = _measurements.value + measurement
        saveMeasurements()
    }
    
    fun deleteMeasurement(measurement: Measurement) {
        _measurements.value = _measurements.value.filter { it.id != measurement.id }
        saveMeasurements()
    }
    
    fun deleteAllMeasurements() {
        _measurements.value = emptyList()
        saveMeasurements()
    }
    
    fun exportToCSV(): String {
        var csv = Measurement.csvHeader() + "\n"
        csv += _measurements.value.joinToString("\n") { it.toCSV() }
        return csv
    }
    
    fun exportToJSON(): String {
        return gson.toJson(_measurements.value)
    }
}

