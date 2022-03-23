<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use DB;

class RoomController extends Controller
{
    public function show(){
        return view('dashboard', [
            'room' => \App\Models\Room::first()
        ]);
    }

    public function add($roomName, $number){
        DB::table('rooms')->insert([
            'people' => $number,
            'roomName' => $roomName
        ]);
        return redirect('/addRoom');
    }

    public function fillRoom(){
        return view('addRoom');
    }
}
