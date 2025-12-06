# Start BuildBarn Services Script

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "BuildBarn Remote Caching Setup" -ForegroundColor Cyan
Write-Host "========================================`n" -ForegroundColor Cyan

# Check if Docker is running
Write-Host "Checking Docker status..." -ForegroundColor Yellow
$dockerRunning = $false
try {
    docker ps | Out-Null
    $dockerRunning = $true
    Write-Host "✓ Docker is running`n" -ForegroundColor Green
} catch {
    Write-Host "✗ Docker is not running`n" -ForegroundColor Red
    Write-Host "Please start Docker Desktop and run this script again.`n" -ForegroundColor Yellow
    Write-Host "Opening Docker Desktop..." -ForegroundColor Yellow
    Start-Process "C:\Program Files\Docker\Docker\Docker Desktop.exe"
    Write-Host "`nWaiting for Docker to start (this may take a minute)..." -ForegroundColor Yellow
    Write-Host "Once Docker is ready, press Enter to continue..." -ForegroundColor Yellow
    Read-Host
}

# Start BuildBarn services
Write-Host "Starting BuildBarn services..." -ForegroundColor Yellow
docker-compose up -d

if ($LASTEXITCODE -eq 0) {
    Write-Host "`n✓ BuildBarn services started successfully!`n" -ForegroundColor Green
    
    Write-Host "Services running:" -ForegroundColor Cyan
    Write-Host "  - bb-storage:  gRPC on port 8980, HTTP on port 7980" -ForegroundColor White
    Write-Host "  - bb-browser:  Web UI on http://localhost:8081`n" -ForegroundColor White
    
    Write-Host "Waiting for services to be ready..." -ForegroundColor Yellow
    Start-Sleep -Seconds 5
    
    Write-Host "`nChecking service status:" -ForegroundColor Cyan
    docker-compose ps
    
    Write-Host "`n========================================" -ForegroundColor Cyan
    Write-Host "Next Steps:" -ForegroundColor Cyan
    Write-Host "========================================" -ForegroundColor Cyan
    Write-Host "1. View Web UI: http://localhost:8081" -ForegroundColor White
    Write-Host "2. Clean local cache: bazel clean" -ForegroundColor White
    Write-Host "3. Build with remote cache: bazel build --config=remote-cache //c_project/automotive:automotive_app" -ForegroundColor White
    Write-Host "4. Rebuild to see cache hits!`n" -ForegroundColor White
    
    $openBrowser = Read-Host "Open BuildBarn Web UI in browser? (Y/n)"
    if ($openBrowser -ne "n") {
        Start-Process "http://localhost:8081"
    }
} else {
    Write-Host "`n✗ Failed to start BuildBarn services" -ForegroundColor Red
    Write-Host "Check logs with: docker-compose logs`n" -ForegroundColor Yellow
}
