use serde::{Deserialize, Serialize};
use serde_json::Value;
use std::cmp::min;
use std::path::Path;
use std::{clone, fs, io};
fn str_to_i32(str: String) -> i32 {
    let mut cnt: i32 = 0;
    for i in str.as_bytes() {
        cnt *= 10;
        cnt += *i as i32 - '0' as i32;
    }
    cnt
}
#[derive(Deserialize)]
struct Train {
    data: Vec<Value>,
}
impl Train {
    fn get_price_yz(&self) -> i32 {
        let mut min_price = 0x3f3f3f3f;
        for i in &self.data {
            //let class_name = i["queryLeftNewDTO"]["train_class_name"].as_str().expect("msg");
            if  !i["queryLeftNewDTO"]["yz_price"].is_null(){
                let j = str_to_i32(
                    i["queryLeftNewDTO"]["yz_price"]
                        .as_str()
                        .expect("err in for")
                        .to_string(),
                );
                min_price = min(j, min_price);
            }
        }
        min_price
    }
    fn load(path_in: String) -> Train {
        let jsdata = fs::read_to_string(path_in).expect("msg");
        let trains = serde_json::from_str::<Value>(&jsdata).expect("msg");
        serde_json::from_value(trains).expect("msg")
    }
}

fn main() -> Result<(), io::Error> {
    let station_lists = [
        "BJP", "TJP", "SJP", "TYV", "SYT", "CCT", "SHH", "NJH", "HZH", "HFH", "XMS", "NCG", "QDK",
        "ZZF", "WHN", "CSQ", "GLZ", "SEQ", "GIW", "KMM", "LSO", "XAY",
    ];
    print!("    ");
    for station in station_lists{
        print!("{}  ",station);
    }
    print!("\n");
    for stationF in station_lists {
        print!("{}  ",stationF);
        for stationT in station_lists {
            if stationF == stationT {
                print!("0   ");
                continue;
            }
            let path_in = format!("stationdata/{}_{}.data",stationF,stationT);
            //let path_in = "stationdata/BJP_TJP.data".to_string();
            let s = Train::load(path_in);
            let mut price = s.get_price_yz();
            if price == 1061109567{
                price = -1;
            }
            print!("{}  ", price);
            //println!("{}",path_in);
        }
        print!("\n");
        
    }
    Ok(())
}
