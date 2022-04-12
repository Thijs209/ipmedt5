<?php

namespace Database\Seeders;

use Illuminate\Database\Seeder;
use DB;

class roomsSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        DB::table('rooms')->insert([
            'id' => 'room1',
            'people' => 0,
            'roomName' => 'de kamer'
        ]);
    }
}
