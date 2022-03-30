<?php

namespace Database\Seeders;

use Illuminate\Database\Seeder;
use DB;
class detectSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        DB::table('detect')->insert([
            'room_name' =>"een",
        ]);
    }
}
