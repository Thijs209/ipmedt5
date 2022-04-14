@extends('default')

@section('title')
    {{"Lightly - Dashboard"}}
@endsection
@section('content')

@section('script')
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
<script src="https://js.pusher.com/7.0/pusher.min.js"></script>
<script>
    var pusher = new Pusher('45da88aa7f5d38d338c4', {
    cluster: 'eu'
    });

    var channel = pusher.subscribe('my-channel');
    channel.bind('dashboard-update', function() {
        location.reload();
    });
</script>
@endsection('script')
<main>
        @foreach($rooms as $lightRoom)
            <section class="lamp_sectie">
                <form class="lamp_knop" method='POST' action='/light-switch'>
                    @csrf
                    <figure class="lamp_bol"></figure>
                    @if ($lightRoom->light_status == 0) 
                        <img class="lamp_img" src="img/light-bulb_uit.png" alt="De lamp staat uit." width="111" height="104">
                    @else
                        <img class="lamp_img" src="img/light-bulb_aan.png" alt="De lamp staat aan." width="111" height="104">
                    @endif
                    <input type='hidden' name='id' value='{{$lightRoom->id}}'>
                    <input class='light-button' type='submit' value=''>
                </form>
                <h2 class="lamp_tekst">{{$lightRoom->roomName}}</h2>
                <p class="lamp_aantalMensen" data-quantity="0">aantal mensen: {{$lightRoom->people}}</p>
                <form class="aanpassen" action='/update' method='POST'>
                    @csrf
                    <label for='people'>Personen aanpassen</label>
                    <input class="invullen" name='people' type='number' value=0>
                    <input type='hidden' name='roomName' value='{{$lightRoom->roomName}}'>
                    <input class="wijzig" type='submit' value="Wijzig">
                </form>
            </section>
        @endforeach
    </main>
@endsection