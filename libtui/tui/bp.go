package tui

import (
	"bytes"
	"text/template"

	"github.com/pterm/pterm"
)


type Colors struct {
	Red          string
	Yellow       string
	Green        string
	Cyan         string
	Blue         string
	Magenta      string
	LightRed     string
	LightYellow  string
	LightGreen   string
	LightCyan    string
	LightBlue    string
	LightMagenta string
	Gray         string
	Reset        string
}

type PrintTemplate struct {
	Cl Colors
}

type Nuker struct {
	GuildID string
	Token   string
}


func BetterPrint(text string) {

	template := NewColors()

	formattedText, err := formatText(text, template)

	if err != nil {
		pterm.Printf("There was an error while formatting the text: %s", err)
		return
	}

	pterm.Print(formattedText)
}

func formatText(text string, textStruct interface{}) (string, error) {

    tmpl, err := template.New("bp").Parse(text)
    if err != nil {
        return "", err
    }

    var buf bytes.Buffer

    err = tmpl.Execute(&buf, textStruct)
    if err != nil {
        panic(err)
    }

    result := buf.String()

    return result, nil
}


func NewColors() Colors {
	return Colors{
		Red:          "\033[31m",
		Yellow:       "\033[33m",
		Green:        "\033[32m",
		Cyan:         "\033[36m",
		Blue:         "\033[34m",
		Magenta:      "\033[35m",
		LightRed:     "\033[91m",
		LightYellow:  "\033[93m",
		LightGreen:   "\033[92m",
		LightCyan:    "\033[96m",
		LightBlue:    "\033[94m",
		LightMagenta: "\033[95m",
		Gray:         "\033[90m",
		Reset: 		  "\033[0m",
	}
}