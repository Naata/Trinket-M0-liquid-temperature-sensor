param(
    [string]$filePath = $(throw "filePath not specified"),
    [string]$com = $(throw "COM port not specified")
)
[System.IO.Ports.SerialPort]$port = new-Object System.IO.Ports.SerialPort $com, 9600, None, 8, one
$port.DtrEnable = $true
try {
    Write-Host 'checking if port is open...'
    if ($port.IsOpen) {
        Write-Host 'port is open, closing...'
        $port.Close();
    }
    Write-Host 'port is closed'
    Write-Host 'opening port...'
    $port.Open()
    Write-Host 'done'
    while ($port.IsOpen) {
        try {
            $line = $port.ReadLine();
            $line = $line.Trim();
            $value = [math]::Round($line);
            Set-Content -Path $filePath -Value $value
        } catch {
            # don't do anything when read/write fail
        }
    }
}
finally {
    if ($port.IsOpen) { $port.Close() }
}
