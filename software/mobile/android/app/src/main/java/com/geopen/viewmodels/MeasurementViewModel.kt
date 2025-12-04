package com.geopen.viewmodels

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.geopen.models.Measurement
import com.geopen.services.BLEManager
import com.geopen.services.DataManager
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.launch

class MeasurementViewModel(
    private val bleManager: BLEManager,
    private val dataManager: DataManager = DataManager.getInstance()
) : ViewModel() {
    
    val measurements: StateFlow<List<Measurement>> = dataManager.measurements.asStateFlow()
    
    fun saveMeasurement(measurement: Measurement) {
        viewModelScope.launch {
            dataManager.saveMeasurement(measurement)
        }
    }
    
    fun deleteMeasurement(measurement: Measurement) {
        viewModelScope.launch {
            dataManager.deleteMeasurement(measurement)
        }
    }
    
    fun exportToCSV(): String {
        return dataManager.exportToCSV()
    }
    
    fun exportToJSON(): String {
        return dataManager.exportToJSON()
    }
}

