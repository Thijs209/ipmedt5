<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Document</title>
</head>
<body>
    <form class="addRoomForm" action="/room" method="POST">
        @csrf
        <section>
            <label for="roomID">Kamer Nummer</label><br>
            <select name="roomID" id="roomID">
                @foreach ($rooms as $room)
                    <option value="{{$room->roomID}}">{{$room->roomName}}</option> 
                @endforeach
            </select>
        </section>

        <section class="roomNameSection">
            <label for="roomNameField">Kamer Naam</label><br>
            <input id="roomNameField" name="roomName" type="text"><br>
        </section>
    
        <section class="numberPeopleSection">
            <label for="numberPeopleField">Hoeval mensen zijn er in de kamer?</label><br>
            <input id="numberPeopleField" name="people" type="number" value="0"><br>
        </section>

        <input type="submit" value="Submit" id="submit">
    </form>
</body>
</html>