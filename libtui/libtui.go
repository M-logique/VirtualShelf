package main


/*
#cgo CXXFLAGS: -std=c++14
#cgo CFLAGS: -I./../include
#cgo LDFLAGS: -L./libtui -lstdc++
#include "shared.h"
*/
import "C"

import (
	"fmt"
	"libtui/tui"
	"time"

	"github.com/pterm/pterm"
)

//export GoPrintLogo
func GoPrintLogo() {
	tui.PrintLogo()
}

//export GoGetMenuChoice
func GoGetMenuChoice() int {
	return tui.MenuChoice()
}

//export GoTypeText
func GoTypeText(text *C.char) {
	goText := C.GoString(text)

	tui.TypeText(
		goText,
		time.Millisecond * 5,
		pterm.NewRGB(0, 255, 255),
		pterm.NewRGB(80, 80, 80),
	)
}

//export GoPressEnter
func GoPressEnter() {
	fmt.Println()
	tui.TypeText(
		"Press enter to continue...", 
		time.Millisecond * 10, 
		pterm.NewRGB(0, 255, 255),
		pterm.NewRGB(80, 80, 80),
	)
	fmt.Scanln()
}

//export GoUpdateRGBState
func GoUpdateRGBState() {
	tui.RgbEnabled = int(C.is_rgb_enabled())
}

//export GoBetterPrint
func GoBetterPrint(text *C.char) {
	goText := C.GoString(text)
	tui.BetterPrint(goText)
}


func main() {}