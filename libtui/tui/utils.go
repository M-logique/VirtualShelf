package tui

import (
	"strings"

	"github.com/pterm/pterm"
)

func fade(text string, startColor pterm.RGB, endColor pterm.RGB) {
	txt := ""

	splittedText := strings.Split(text, "")

	for i := 0; i < len(splittedText); i++ {
		fadeFactor := float32(i) / float32(len(splittedText))

		currentColor := startColor.Fade(0, 1, fadeFactor, endColor)
		txt += currentColor.Sprint(splittedText[i])
	}
	pterm.Println(txt)
}