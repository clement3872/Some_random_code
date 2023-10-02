
pub struct Song {
    rank: u32,
    title: String,
}

/*
fn sorted_songs_by_rank(songs:Vec<Song>){
    let mut new_songs: Vec<Song> = vec![songs[0]];
    for i in 0..(songs.len()){
        println!("{}", songs[i].rank)
    }
}
*/ 

impl Song {
    fn display(&self){
        println!("title: {}, rank: {}", self.title, self.rank);
    }
}


pub fn display_songs(songs:&Vec<Song>){
    for song in songs{
        song.display();
    }
}

pub fn average_songs(songs:&Vec<Song>) -> f64{
    // here we take a reference to not change the ownership
    let mut avg: f64 = 0.;
    for song in songs{
        avg += song.rank as f64;
    }

    avg/(songs.len() as f64)
}

pub fn filter_song(songs:Vec<Song>, rank_min: u32) -> Vec<Song>{
    let mut vec: Vec<Song> = Vec::new();

    for song in songs{
        if song.rank > rank_min {
            vec.push(song);
        }
    }
    vec
}

pub fn good_songs(songs: Vec<Song>) -> Vec<Song>{
    let avg = average_songs(&songs) as u32;
    filter_song(songs, avg)
}

pub fn do_song(){
    let songs : Vec<Song> = vec![
     Song {
         rank: 4,
         title: String::from("Stairway to Heaven"),
     },
     Song {
         rank: 2,
         title: String::from("Never Gonna Give You Up"),
     },
     Song {
         rank: 5,
         title: String::from("Nigerian Marketplace"),
     },
    ];

    // display_songs(songs);
    // println!("{}", average_songs(&songs));
    println!("Before filter");
    display_songs(&songs);
    println!("After filter");
    display_songs(&filter_song(songs, 3));
}
