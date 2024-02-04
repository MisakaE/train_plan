"""Console script for get_sta_js."""
import sys
import click
import requests
import json
from urllib.parse import urlencode
from time import sleep

headers = {
    'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64; rv:122.0) Gecko/20100101 Firefox/122.0',
    'Cookie': 'JSESSIONID=63EF8264D44D4E94823B7491E523EE66; guidesStatus=off; _jc_save_fromStation=%u5170%u5DDE%2CLZJ; _jc_save_toStation=%u897F%u5B89%2CXAY; _jc_save_fromDate=2024-01-26; _jc_save_toDate=; _jc_save_wfdc_flag=dc; BIGipServerpassport=988283146.50215.0000; highContrastMode=defaltMode; cursorStatus=off; route=9036359bb8a8a461c164a04f8f50b252; BIGipServerotn=2581004554.64545.0000; BIGipServerportal=3151233290.16671.0000'
}

def get_tickets(fromwhere,towhere,startime):
    #数据字典
    data = {
        'leftTicketDTO.train_date': startime,
        'leftTicketDTO.from_station': fromwhere,
        'leftTicketDTO.to_station': towhere,
        'purpose_codes': 'ADULT',
    }
    #构造请求链接：地址 + 参数 （startime,fromwhere,wowhere）
    request_url = 'https://kyfw.12306.cn/otn/leftTicketPrice/queryAllPublicPrice?' + urlencode(data)
    #print(request_url)
    response = requests.get(request_url,headers=headers).text
    
    return response
def run():
    lists_station = ['BJP','TJP','SJP','TYV','SYT','CCT','SHH','NJH','HZH','HFH','XMS','NCG','QDK','ZZF','WHN','CSQ','GLZ','SEQ','GIW','KMM','LSO','XAY']
    for stationF in lists_station:
        for stationT in lists_station:
            if stationF == stationT:
                continue
            path_in=stationF+'_'+stationT+'.data'
            sys.stdout = open(path_in, 'w')
            lists = get_tickets(stationF,stationT,'2024-02-01')
            print(lists)
            sleep(5.5)
    #lists = get_tickets('WAR','CDW','2024-02-01')
    #sys.stdout = open(path_in, 'w')
    #print(lists)


@click.command()
def main(args=None):
    run()
    return 0


if __name__ == "__main__":
    sys.exit(main())  # pragma: no cover
