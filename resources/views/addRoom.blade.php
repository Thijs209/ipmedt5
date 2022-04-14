@extends('default')

@section('title')
    {{"Lightly - Kamer toevoegen"}}
@endsection

@section('content')
<main class='add-main'>
    <form action="/room" method="POST" class='add-form'>
        @csrf
        <label for="id">Kamer Nummer</label>
        <select name="id" id="id">
            @foreach ($rooms as $room)
                <option value="{{$room->id}}">{{$room->roomName}}</option>                  
            @endforeach
        </select>

        <label for="roomNameField">Kamer Naam</label>
        <input id="roomNameField" name="roomName" type="text">
    
        <label for="numberPeopleField">Hoeval mensen zijn er in de kamer?</label>
        <input id="numberPeopleField" name="people" type="number" value="0">
        
        <input type="submit" value="Submit" id="submit">
    </form>
</main>
@endsection('content')