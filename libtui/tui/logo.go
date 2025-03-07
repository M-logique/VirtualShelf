package tui

import (
	"strings"

	"github.com/pterm/pterm"
)


func PrintLogo() {
	logo := `
.    _    ___      __              __   _____ __         ______
.   | |  / (_)____/ /___  ______ _/ /  / ___// /_  ___  / / __/
.   | | / / / ___/ __/ / / / __  / /   \__ \/ __ \/ _ \/ / /_  
.   | |/ / / /  / /_/ /_/ / /_/ / /   ___/ / / / /  __/ / __/  
.   |___/_/_/   \__/\__,_/\__,_/_/   /____/_/ /_/\___/_/_/
.
.           .--.          .---.        .-.
.       .---|--|   .-.    | H |  .---. |~|    .--.
.	.--|===|  |---|_|--.__| A |--|:::| |~|-==-|==|---.
.	|%%| I |  |===| |~~|%%| T |--|   |_|~|PROG|  |___|-.
.	|  |   |  |===| |==|  | E |  |:::|=| |RAMM|  |---|=|
.	|  |   |  |   |_|__|  |   |__|   | | |ING |  |___| |
.	|~~|===|--|===|~|~~|%%|~~~|--|:::|=|~|----|==|---|=|
.	^--^---'--^---^-^--^--^---'--^---^-^-^-==-^--^---^-'                                             
`	
	// fade(logo, pterm.NewRGB(0, 255, 255), pterm.NewRGB(80, 80, 80))

	// txt := ""
	startColor :=  pterm.NewRGB(0, 255, 255)
	endColor := pterm.NewRGB(90, 80, 80)

	splittedText := strings.Split(logo, "\n")

	for i := 0; i < len(splittedText); i++ {
		fadeFactor := float32(i) / float32(len(splittedText))

		currentColor := startColor.Fade(0, 1, fadeFactor, endColor)
		// txt += currentColor.Sprint(splittedText[i])
		currentColor.Println(splittedText[i])
	}
	// pterm.Println(txt)
}

