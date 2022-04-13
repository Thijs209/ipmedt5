<!DOCTYPE html>
<html lang="nl">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="css/main.css">
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Poiret+One&display=swap" rel="stylesheet">
    <title>Lightly | Lampen</title>
</head>
<body>
    <header><!--Lightly--><!--helemaal rechts: link naar logs-->
        <h1>Lightly</h1>
        <button class="naar_log" type="button" onclick="window.location='logs.html'">Logs</button>
    </header>
    <main>
        @foreach($room as $lightRoom)
            <section class="lamp_sectie" type="button" state="off" onclick="lamp_toggle(this)">
                <form class="lamp_knop">
                    <figure class="lamp_bol"></figure>
                    <img class="lamp_img" src="img/light-bulb_uit.png" alt="Knop die aangeeft of een lamp aan of uit staat." width="111" height="104">
                </form>
                <p class="lamp_callibreer" onclick="callibreren()">callibreer</p>
                <h2 class="lamp_tekst">{{$lightRoom->roomName}}</h2>
                <p class="lamp_aantalMensen" data-quantity="0">aantal mensen: {{$lightRoom->people}}</p>
                <form action='/update' method='POST'>
                    @csrf
                    <label for='people'>Personen aanpassen</label>
                    <input class="invullen" id='people' name='people' type='number'}>
                    <input type='hidden' id='roomName' name='roomName' value='{{$lightRoom->roomName}}'>
                    <input type='submit'>Wijzig</input>
                </form>
            </section>
        @endforeach
    </main>
</body>
</html>