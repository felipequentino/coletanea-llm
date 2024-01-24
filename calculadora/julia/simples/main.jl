#= import Pkg
Pkg.add("Gtk")
 =#
#TESTAR NO WINDOWS
using Gtk

function criar_calculadora()
    win = Gtk.Window("Calculadora")
    vbox = Gtk.VBox(spacing=6)

    entry = Gtk.Entry()
    vbox_pack_start(vbox, entry, expand=true, fill=true, padding=0)

    botoes = [
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", ".", "=", "+"
    ]

    grid = Gtk.Grid(column_spacing=6, row_spacing=6)
    for (i, label) in enumerate(botoes)
        button = Gtk.Button(label)
        signal_connect(button, "clicked") do widget
            on_botao_clicado(widget, entry)
        end
        grid_attach(grid, button, (i-1) % 4 + 1, div(i-1, 4) + 1, 1, 1)
    end

    vbox_pack_start(vbox, grid, expand=true, fill=true, padding=0)

    signal_connect(win, "destroy") do widget
        Gtk.main_quit()
    end

    container_add(win, vbox)

    showall(win)
end

function on_botao_clicado(widget, entry)
    text = get_text(widget)

    if text == "="
        try
            resultado = eval(parse(get_text(entry)))
            set_text(entry, string(resultado))
        catch e
            set_text(entry, "Erro")
        end
    else
        append_text(entry, text)
    end
end

function main()
    Gtk.GtkMain.init()
    criar_calculadora()
    Gtk.main()
end

main()
