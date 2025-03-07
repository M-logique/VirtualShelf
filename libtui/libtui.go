package main

import "C"

import (
	"libtui/tui"
	"time"

	"github.com/pterm/pterm"
)

//export PrintLogo
func PrintLogo() {
	tui.PrintLogo()
}

//export GetMenuChoice
func GetMenuChoice() int {
	return tui.MenuChoice()
}

//export TypeText
func TypeText(text *C.char) {
	goText := C.GoString(text)

	tui.TypeText(
		goText,
		time.Millisecond * 20,
		pterm.NewRGB(0, 255, 255),
		pterm.NewRGB(80, 80, 80),
	)
}

func main() {}