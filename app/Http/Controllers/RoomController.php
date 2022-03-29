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

    public function store(Request $request, \App\Models\Room $room){
        $room->roomName = $request->input('roomName');
        $room->people = $request->input('people');

        try{
            $room->save();
            return redirect('/');
        } catch(Exception $e){
            return redirect('/addRoom');
        }
    }

    public function create(){
        return view('addRoom');
    }
}
