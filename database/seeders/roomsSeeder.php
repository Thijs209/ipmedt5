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
            'id' => '1',
        ]);

        DB::table('rooms')->insert([
            'id' => '2',
        ]);

        DB::table('rooms')->insert([
            'id' => '3',
        ]);
    }
}
