window.onload = () => {
    const knoppen = document.getElementsByClassName("lamp_knop");

    for (let i = 0; i < knoppen.length; i++) {
        knoppen[i].addEventListener("click", lamp_toggle(this));
    }
}

//Zorgt dat alle info op de site gelijk wordt aan de info in de db
state_ophalen = () => {
    var lampen = [false] //@Nils: moet eigenlijk uit database gehaald. Staat nu slechts één element in; woonkamer, maar zou kunnen uitgebreid.
    const knoppen = document.getElementsByClassName("lamp_knop");
    for (let i = 0; i < lampen.length(); i++) {
        if (lampen[i] == true) {
            knoppen[i].state = "on";
            knoppen[i].children[1].src = "img/light-bulb_on";
        }
        else if (lampen[i] == false) {
            knoppen[i].state = "off";
            knoppen[i].children[1].src = "img/light-bulb_off";
        }
        //knoppen[i].children[5].dataset.quantity =     @Nils, dit moet uit de db gehaald, ter controle
    }
}

lamp_toggle = (knop) => {
    if (knop.state == "on") {
        //@Nils: in de database moet de staat naar uit veranderd worden en het aantal mensen naar 0.
    }
    else {
        //@Janna: vragen hoeveel mensen er dan in de kamer zijn, stop dat in [aantal].
        //@Nils: in de database moet de staat naar aan veranderd worden en het aantal mensen naar [aantal].
    }
    state_ophalen();
}

//@Nils: hieronder moet gecallibreerd worden, ik heb geen plan hoe (en wat het zou betekenen), maar dat heeft ws vooral te maken met de db
/*callibreer = () => {

}
*/


