const { app, globalShortcut, BrowserWindow } = require('electron')

function createWindow() {
	const win = new BrowserWindow({
		width: 1180,
		height: 700,
		webPreferences: {
			nodeIntegration: true
		}
	})

	win.removeMenu()
	win.setMaximizable(false)
	win.setResizable(false)
	win.loadFile('public/index.html')

	// Show dev tools when pressing Ctrl+Shift+I on keyboard
	globalShortcut.register("CmdOrCtrl+Shift+I", () => {
		win.isFocused() && win.webContents.toggleDevTools()
	})
}

app.whenReady().then(createWindow)

app.on('window-all-closed', () => {
	if (process.platform !== 'darwin') {
		app.quit()
	}
})

app.on('activate', () => {
	if (BrowserWindow.getAllWindows().length === 0) {
		createWindow()
	}
})
