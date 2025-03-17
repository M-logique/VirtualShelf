package tui

import (
	"strings"
	"time"

	"github.com/pterm/pterm"
)

func fade(text string, startColor pterm.RGB, endColor pterm.RGB) {
	txt := ""

	if RgbEnabled == 1 {
		splittedText := strings.Split(text, "")
	
		for i := 0; i < len(splittedText); i++ {
			fadeFactor := float32(i) / float32(len(splittedText))
	
			currentColor := startColor.Fade(0, 1, fadeFactor, endColor)
			txt += currentColor.Sprint(splittedText[i])
		}
	} else {
		txt = text;
	}
	pterm.Print(txt)
}

func TypeText(text string, sleepDuration time.Duration, startColor pterm.RGB, endColor pterm.RGB) {
	splittedText := strings.Split(text, "")

	for i := 0; i < len(splittedText); i++ {
		fadeFactor := float32(i) / float32(len(splittedText))

		
		time.Sleep(sleepDuration)
		if RgbEnabled == 1 {
			currentColor := startColor.Fade(0, 1, fadeFactor, endColor)
			currentColor.Print(splittedText[i])
		} else {
			pterm.Print(splittedText[i])
		}
	}

}