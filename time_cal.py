def length(integer:int):
    return len(str(integer))

def add_time(start, duration,weeks=''):
    day_later=0
    lists="".join(c for c in start if c.isalpha())
    times="".join(c for c in start if not c.isalpha()).split(':')
    added_time=duration.split(':')
    day_names = [         
        'monday',         
        'tuesday',         
        'wednesday',         
        'thursday',         
        'friday',         
        'saturday',
        'sunday',    
        ]
    Day_names = [         
        'Monday',         
        'Tuesday',         
        'Wednesday',         
        'Thursday',         
        'Friday',         
        'Saturday',
        'Sunday',    
        ]
    print(lists)
    print(times,added_time)
    for i in range(len(times)):
        num=int(times[i])+int(added_time[i])
        times[i]=str(num)
    if int(times[1])>=60:
        times[1]=str(int(times[1])-60)
        times[0]=str(int(times[0])+1)
    # if int(times[0])>12 and AM_PM:
    #     if int(times[0])<25:
    #         times[0]=str(int(times[0])-12)
    #         AM_PM=False
    #     else:
    #         day_later=int(times[0]/24)
    #         times[0]=times[0]-day_later*24
    # elif int(times[0])>12 and not AM_PM:
    #     day_later=int((times[0]+12)/24)
    #     times[0]=times[0]-day_later*24+12
    # if day_later==1:
    #     return 
    # print(times,AM_PM)
    # print(int(5/3))
    times_of_day=''
    if lists=='PM':
        times[0]=str(int(times[0])+12)
    if int(times[0])>=24:
        day_later=int(int(times[0])/24)
    current_time=int(times[0])-24*day_later
    print(times,day_later)
    if len(times[1])==1:
        times[1]=f"0{times[1]}"
    if current_time>=12:
        if current_time>12:
            current_time=current_time-12
        times_of_day='PM'
    else:
        if current_time==0:
            current_time=12
        times_of_day='AM'

    times[0]=str(current_time)
    end_day=''
    if not weeks=='':
        weeks=weeks.lower()
        i=0
        j=0
        for day in day_names:
            if weeks==day:
                j=i
            i+=1
        j+=day_later
        j=j%7
        i=0
        for day in Day_names:
            if j==i:
                end_day=day
            i+=1

    
    

    

    new_time=f'{times[0]}:{times[1]} {times_of_day}'
    if not weeks=='':
        new_time+=f', {end_day}'
    if day_later==1:
        new_time+= ' (next day)'
    elif day_later>1:
        new_time+= f' ({day_later} days later)'
    print(new_time)
    return new_time

add_time('3:30 PM', '2:12', 'Monday')
