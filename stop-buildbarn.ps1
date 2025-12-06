# Stop BuildBarn Services Script

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Stopping BuildBarn Services" -ForegroundColor Cyan
Write-Host "========================================`n" -ForegroundColor Cyan

$option = Read-Host "Choose an option:`n1. Stop services (keep cache)`n2. Stop and remove containers (keep cache)`n3. Stop, remove containers and delete cache`n`nEnter option (1-3)"

switch ($option) {
    "1" {
        Write-Host "`nStopping services..." -ForegroundColor Yellow
        docker-compose stop
        Write-Host "✓ Services stopped (use 'docker-compose start' to resume)" -ForegroundColor Green
    }
    "2" {
        Write-Host "`nStopping and removing containers..." -ForegroundColor Yellow
        docker-compose down
        Write-Host "✓ Containers removed (cache preserved)" -ForegroundColor Green
    }
    "3" {
        Write-Host "`nStopping, removing containers, and deleting cache..." -ForegroundColor Yellow
        docker-compose down -v
        Write-Host "✓ Everything removed (fresh start next time)" -ForegroundColor Green
    }
    default {
        Write-Host "Invalid option. Stopping services only..." -ForegroundColor Yellow
        docker-compose stop
    }
}

Write-Host "`nDone!`n" -ForegroundColor Cyan
