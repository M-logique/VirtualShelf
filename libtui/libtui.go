package main

import "C"

import "libtui/tui"

//export PrintLogo
func PrintLogo() {
	tui.PrintLogo()
}

//export GetMenuChoice
func GetMenuChoice() int {
	return tui.MenuChoice()
}

func main() {}