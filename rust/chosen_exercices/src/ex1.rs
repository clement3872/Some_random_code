
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

pub fn average_rank(songs:&Vec<Song>) -> f64{
    // here we take a reference to not change the ownership
    if songs.len()>0{
        let mut avg: f64 = 0.;
        for song in songs{
            avg += song.rank as f64;
        }
        
        avg/(songs.len() as f64)
    }
    else{
        panic!();
    }
}

pub fn filter_songs(songs:Vec<Song>, rank_min: u32) -> Vec<Song>{
    let mut vec: Vec<Song> = Vec::new();

    for song in songs{
        if song.rank > rank_min {
            vec.push(song);
        }
    }
    vec
}

pub fn good_songs(songs: Vec<Song>) -> Vec<Song>{
    let avg = average_rank(&songs) as u32;
    filter_songs(songs, avg)
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

    display_songs(&songs);
    println!("{}", average_rank(&songs));

    /*
    println!("Before filter");
    display_songs(&songs);
    println!("After filter");
    display_songs(&filter_songs(songs, 3));
    */
}




#[cfg(test)]
mod tests {
    use super::*;

    fn example() -> Vec<Song> {
        vec![
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
        ]
    }

    #[test]
    #[should_panic]
    fn empty() {
        let sgs = Vec::new();
        let _m = average_rank(&sgs);
    }

    #[test]
    fn moyenne_un_seul_morceau() {
        let sgs = vec![Song {
            rank: 4,
            title: String::from("Stairway to Heaven"),
        }];
        let m = average_rank(&sgs);
        assert_eq!(m, 4.0);
    }

    #[test]
    fn moyenne_plusieurs_morceau() {
        let sgs = example();
        let m = average_rank(&sgs);
        assert!((m - 3.66666).abs() < 0.001);
    }

    #[test]
    fn filtre() {
        let sgs = example();
        let f = filter_songs(sgs, 4);
        assert!(f.len() == 1);
        assert_eq!(f[0].rank, 5);
        assert_eq!(f[0].title, "Nigerian Marketplace");
    }

    #[test]
    fn meilleurs() {
        let sgs = example();
        let f = good_songs(sgs);
        assert!(f.len() == 2);
        for m in &f {
            assert!(m.rank >= 4);
        }
    }
}
