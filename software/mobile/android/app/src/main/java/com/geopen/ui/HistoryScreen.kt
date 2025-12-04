package com.geopen.ui

import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Delete
import androidx.compose.material.icons.filled.Share
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import com.geopen.models.Measurement
import com.geopen.viewmodels.MeasurementViewModel

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun HistoryScreen(viewModel: MeasurementViewModel) {
    val measurements by viewModel.measurements.collectAsState()
    var searchText by remember { mutableStateOf("") }
    var showingExportSheet by remember { mutableStateOf(false) }
    
    val filteredMeasurements = if (searchText.isEmpty()) {
        measurements
    } else {
        measurements.filter { measurement ->
            measurement.coreSampleId?.contains(searchText, ignoreCase = true) == true ||
            measurement.projectId?.contains(searchText, ignoreCase = true) == true ||
            measurement.operatorId?.contains(searchText, ignoreCase = true) == true
        }
    }
    
    Scaffold(
        topBar = {
            TopAppBar(
                title = { Text("History") },
                actions = {
                    IconButton(onClick = { showingExportSheet = true }) {
                        Icon(Icons.Default.Share, contentDescription = "Export")
                    }
                }
            )
        }
    ) { padding ->
        if (filteredMeasurements.isEmpty) {
            EmptyHistoryView()
        } else {
            Column(modifier = Modifier.padding(padding)) {
                OutlinedTextField(
                    value = searchText,
                    onValueChange = { searchText = it },
                    label = { Text("Search") },
                    modifier = Modifier
                        .fillMaxWidth()
                        .padding(16.dp),
                    singleLine = true
                )
                
                LazyColumn(
                    modifier = Modifier.fillMaxSize(),
                    contentPadding = PaddingValues(16.dp),
                    verticalArrangement = Arrangement.spacedBy(8.dp)
                ) {
                    items(
                        items = filteredMeasurements,
                        key = { it.id }
                    ) { measurement ->
                        MeasurementRowCard(
                            measurement = measurement,
                            onDelete = { viewModel.deleteMeasurement(measurement) }
                        )
                    }
                }
            }
        }
        
        if (showingExportSheet) {
            ExportBottomSheet(
                measurements = filteredMeasurements,
                onDismiss = { showingExportSheet = false }
            )
        }
    }
}

@Composable
fun MeasurementRowCard(
    measurement: Measurement,
    onDelete: () -> Unit
) {
    Card(
        modifier = Modifier.fillMaxWidth(),
        elevation = CardDefaults.cardElevation(defaultElevation = 2.dp)
    ) {
        Row(
            modifier = Modifier
                .fillMaxWidth()
                .padding(16.dp),
            horizontalArrangement = Arrangement.SpaceBetween,
            verticalAlignment = Alignment.CenterVertically
        ) {
            Column(modifier = Modifier.weight(1f)) {
                Text(
                    text = "α: ${measurement.alphaFormatted()}  β: ${measurement.betaFormatted()}",
                    style = MaterialTheme.typography.titleMedium
                )
                
                if (measurement.coreSampleId != null) {
                    Text(
                        text = "Core: ${measurement.coreSampleId}",
                        style = MaterialTheme.typography.bodySmall,
                        color = MaterialTheme.colorScheme.onSurfaceVariant
                    )
                }
                
                if (measurement.projectId != null) {
                    Text(
                        text = "Project: ${measurement.projectId}",
                        style = MaterialTheme.typography.bodySmall,
                        color = MaterialTheme.colorScheme.onSurfaceVariant
                    )
                }
            }
            
            Column(
                horizontalAlignment = Alignment.End,
                verticalArrangement = Arrangement.spacedBy(4.dp)
            ) {
                Text(
                    text = measurement.timestampFormatted(),
                    style = MaterialTheme.typography.bodySmall,
                    color = MaterialTheme.colorScheme.onSurfaceVariant
                )
                Text(
                    text = "${(measurement.qualityScore * 100).toInt()}%",
                    style = MaterialTheme.typography.bodySmall,
                    color = if (measurement.qualityScore > 0.8) 
                        MaterialTheme.colorScheme.primary 
                    else 
                        MaterialTheme.colorScheme.error
                )
                
                IconButton(onClick = onDelete) {
                    Icon(
                        Icons.Default.Delete,
                        contentDescription = "Delete",
                        tint = MaterialTheme.colorScheme.error
                    )
                }
            }
        }
    }
}

@Composable
fun EmptyHistoryView() {
    Box(
        modifier = Modifier.fillMaxSize(),
        contentAlignment = androidx.compose.ui.Alignment.Center
    ) {
        Column(
            horizontalAlignment = androidx.compose.ui.Alignment.CenterHorizontally,
            verticalArrangement = Arrangement.spacedBy(8.dp)
        ) {
            Text(
                text = "No measurements yet",
                style = MaterialTheme.typography.titleLarge,
                color = MaterialTheme.colorScheme.onSurfaceVariant
            )
            Text(
                text = "Start measuring to see history here",
                style = MaterialTheme.typography.bodyMedium,
                color = MaterialTheme.colorScheme.onSurfaceVariant
            )
        }
    }
}

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun ExportBottomSheet(
    measurements: List<Measurement>,
    onDismiss: () -> Unit
) {
    var exportFormat by remember { mutableStateOf(0) }
    
    ModalBottomSheet(
        onDismissRequest = onDismiss
    ) {
        Column(
            modifier = Modifier
                .fillMaxWidth()
                .padding(24.dp),
            verticalArrangement = Arrangement.spacedBy(16.dp)
        ) {
            Text(
                text = "Export Data",
                style = MaterialTheme.typography.titleLarge
            )
            
            Row(
                modifier = Modifier.fillMaxWidth(),
                horizontalArrangement = Arrangement.spacedBy(8.dp)
            ) {
                FilterChip(
                    selected = exportFormat == 0,
                    onClick = { exportFormat = 0 },
                    label = { Text("CSV") }
                )
                FilterChip(
                    selected = exportFormat == 1,
                    onClick = { exportFormat = 1 },
                    label = { Text("JSON") }
                )
            }
            
            Button(
                onClick = {
                    // Export implementation
                    onDismiss()
                },
                modifier = Modifier.fillMaxWidth()
            ) {
                Text("Export")
            }
        }
    }
}

