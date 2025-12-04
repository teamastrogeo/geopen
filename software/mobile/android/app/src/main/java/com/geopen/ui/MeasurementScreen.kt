package com.geopen.ui

import androidx.compose.foundation.layout.*
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.geopen.models.Measurement
import com.geopen.services.BLEManager
import com.geopen.viewmodels.MeasurementViewModel

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun MeasurementScreen(
    viewModel: MeasurementViewModel,
    bleManager: BLEManager
) {
    val currentMeasurement by bleManager.currentMeasurement.collectAsState()
    val isConnected by bleManager.isConnected.collectAsState()
    val connectionStatus by bleManager.connectionStatus.collectAsState()
    
    var operatorId by remember { mutableStateOf("") }
    var coreSampleId by remember { mutableStateOf("") }
    var projectId by remember { mutableStateOf("") }
    
    Scaffold(
        topBar = {
            TopAppBar(
                title = { Text("GeoPen") }
            )
        }
    ) { padding ->
        Column(
            modifier = Modifier
                .fillMaxSize()
                .padding(padding)
                .padding(16.dp),
            horizontalAlignment = Alignment.CenterHorizontally,
            verticalArrangement = Arrangement.spacedBy(24.dp)
        ) {
            // Connection Status
            ConnectionStatusCard(
                isConnected = isConnected,
                status = connectionStatus
            )
            
            // Measurement Display
            if (currentMeasurement != null) {
                MeasurementDisplayCard(measurement = currentMeasurement!!)
            } else {
                PlaceholderMeasurementCard()
            }
            
            // Controls
            Button(
                onClick = { bleManager.triggerMeasurement() },
                enabled = isConnected,
                modifier = Modifier.fillMaxWidth()
            ) {
                Text("Measure", fontSize = 18.sp)
            }
            
            if (currentMeasurement != null) {
                Button(
                    onClick = {
                        val measurement = currentMeasurement!!
                        val savedMeasurement = measurement.copy(
                            operatorId = operatorId.takeIf { it.isNotEmpty() },
                            coreSampleId = coreSampleId.takeIf { it.isNotEmpty() },
                            projectId = projectId.takeIf { it.isNotEmpty() }
                        )
                        viewModel.saveMeasurement(savedMeasurement)
                        operatorId = ""
                        coreSampleId = ""
                        projectId = ""
                    },
                    colors = ButtonDefaults.buttonColors(
                        containerColor = MaterialTheme.colorScheme.primaryContainer
                    ),
                    modifier = Modifier.fillMaxWidth()
                ) {
                    Text("Save Measurement")
                }
            }
            
            // Metadata Input
            MeasurementMetadataCard(
                operatorId = operatorId,
                coreSampleId = coreSampleId,
                projectId = projectId,
                onOperatorIdChange = { operatorId = it },
                onCoreSampleIdChange = { coreSampleId = it },
                onProjectIdChange = { projectId = it }
            )
        }
    }
}

@Composable
fun ConnectionStatusCard(isConnected: Boolean, status: String) {
    Card(
        modifier = Modifier.fillMaxWidth(),
        colors = CardDefaults.cardColors(
            containerColor = MaterialTheme.colorScheme.surfaceVariant
        )
    ) {
        Row(
            modifier = Modifier.padding(16.dp),
            verticalAlignment = Alignment.CenterVertically,
            horizontalArrangement = Arrangement.spacedBy(8.dp)
        ) {
            Box(
                modifier = Modifier
                    .size(12.dp)
                    .background(
                        color = if (isConnected) MaterialTheme.colorScheme.primary
                        else MaterialTheme.colorScheme.error,
                        shape = androidx.compose.foundation.shape.CircleShape
                    )
            )
            Text(
                text = status,
                style = MaterialTheme.typography.bodyMedium,
                color = MaterialTheme.colorScheme.onSurfaceVariant
            )
        }
    }
}

@Composable
fun MeasurementDisplayCard(measurement: Measurement) {
    Card(
        modifier = Modifier.fillMaxWidth(),
        elevation = CardDefaults.cardElevation(defaultElevation = 4.dp)
    ) {
        Column(
            modifier = Modifier.padding(24.dp),
            horizontalAlignment = Alignment.CenterHorizontally,
            verticalArrangement = Arrangement.spacedBy(24.dp)
        ) {
            // Alpha Angle
            Column(horizontalAlignment = Alignment.CenterHorizontally) {
                Text(
                    text = "Alpha Angle",
                    style = MaterialTheme.typography.titleMedium,
                    color = MaterialTheme.colorScheme.onSurfaceVariant
                )
                Text(
                    text = measurement.alphaFormatted(),
                    style = MaterialTheme.typography.displayLarge,
                    fontWeight = FontWeight.Bold,
                    color = MaterialTheme.colorScheme.primary
                )
                Text(
                    text = "α",
                    style = MaterialTheme.typography.titleLarge,
                    color = MaterialTheme.colorScheme.onSurfaceVariant
                )
            }
            
            Divider()
            
            // Beta Angle
            Column(horizontalAlignment = Alignment.CenterHorizontally) {
                Text(
                    text = "Beta Angle",
                    style = MaterialTheme.typography.titleMedium,
                    color = MaterialTheme.colorScheme.onSurfaceVariant
                )
                Text(
                    text = measurement.betaFormatted(),
                    style = MaterialTheme.typography.displayLarge,
                    fontWeight = FontWeight.Bold,
                    color = MaterialTheme.colorScheme.secondary
                )
                Text(
                    text = "β",
                    style = MaterialTheme.typography.titleLarge,
                    color = MaterialTheme.colorScheme.onSurfaceVariant
                )
            }
            
            // Quality Score
            Row(
                horizontalArrangement = Arrangement.spacedBy(8.dp),
                verticalAlignment = Alignment.CenterVertically
            ) {
                Text(
                    text = "Quality:",
                    style = MaterialTheme.typography.bodyMedium,
                    color = MaterialTheme.colorScheme.onSurfaceVariant
                )
                Text(
                    text = "${(measurement.qualityScore * 100).toInt()}%",
                    style = MaterialTheme.typography.bodyLarge,
                    fontWeight = FontWeight.SemiBold
                )
            }
        }
    }
}

@Composable
fun PlaceholderMeasurementCard() {
    Card(
        modifier = Modifier
            .fillMaxWidth()
            .height(300.dp),
        colors = CardDefaults.cardColors(
            containerColor = MaterialTheme.colorScheme.surfaceVariant
        )
    ) {
        Column(
            modifier = Modifier.fillMaxSize(),
            horizontalAlignment = Alignment.CenterHorizontally,
            verticalArrangement = Arrangement.Center
        ) {
            Text(
                text = "No measurement",
                style = MaterialTheme.typography.titleLarge,
                color = MaterialTheme.colorScheme.onSurfaceVariant
            )
            Spacer(modifier = Modifier.height(8.dp))
            Text(
                text = "Connect device and press Measure",
                style = MaterialTheme.typography.bodyMedium,
                color = MaterialTheme.colorScheme.onSurfaceVariant
            )
        }
    }
}

@Composable
fun MeasurementMetadataCard(
    operatorId: String,
    coreSampleId: String,
    projectId: String,
    onOperatorIdChange: (String) -> Unit,
    onCoreSampleIdChange: (String) -> Unit,
    onProjectIdChange: (String) -> Unit
) {
    Card(
        modifier = Modifier.fillMaxWidth(),
        colors = CardDefaults.cardColors(
            containerColor = MaterialTheme.colorScheme.surfaceVariant
        )
    ) {
        Column(
            modifier = Modifier.padding(16.dp),
            verticalArrangement = Arrangement.spacedBy(12.dp)
        ) {
            Text(
                text = "Measurement Metadata",
                style = MaterialTheme.typography.titleMedium
            )
            
            OutlinedTextField(
                value = operatorId,
                onValueChange = onOperatorIdChange,
                label = { Text("Operator ID") },
                modifier = Modifier.fillMaxWidth(),
                singleLine = true
            )
            
            OutlinedTextField(
                value = coreSampleId,
                onValueChange = onCoreSampleIdChange,
                label = { Text("Core Sample ID") },
                modifier = Modifier.fillMaxWidth(),
                singleLine = true
            )
            
            OutlinedTextField(
                value = projectId,
                onValueChange = onProjectIdChange,
                label = { Text("Project ID") },
                modifier = Modifier.fillMaxWidth(),
                singleLine = true
            )
        }
    }
}

