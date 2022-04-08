<!DOCTYPE html>
<html lang="nl">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>dashboard</title>
</head>
<body>
    
    <h1>Hier komt het dashboard met alle gegevens staan</h1>
    <h2>Kamers</h2>

    @foreach($room as $lightRoom)
        <section>
            <h3>{{$lightRoom->roomName}}</h3>
            <p>Huidig aantal personen: {{$lightRoom->people}}</p>
            <form action='/update' method='POST'>
                @csrf

                <label for='people'>Personen aanpassen</label>
                <input id='people' name='people' type='number'}>

                <input type='hidden' id='roomName' name='roomName' value='{{$lightRoom->roomName}}'>

                <button type='submit'>Wijzig</button>
            </form>
        </section>
    @endforeach
</body>
</html>