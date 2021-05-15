from __future__ import division

import random
import sys


commandStr = ["AddLecture", "GetCourseID", "DeleteLecture",
              "ChangeCourseID", "CalculateScheduleEfficiency", "GetAllFreeRoomsByHour"
              "GetAllLecturesByCourse"]

SUCCESS = "SUCCESS"
FAILURE = "FAILURE"
INVALID_INPUT = "INVALID_INPUT"

LecturesID = dict()
RoomsID = dict()
ExistHours = dict()

size = 0
rooms_count = 0;
lectures_count = 0;
total_hours = 0;


def initline():
    global size, RoomsID, rooms_count, total_hours
    hours = random.randint(1,10)
    rooms = random.randint(5,20)
    inLine = "Init %d %d" %(hours, rooms)
    outLine = "init done."
    rooms_count = rooms
    total_hours = hours
    for i in range(0,rooms):
        RoomsID[i]={};
    return inLine, outLine


# AddLecture hour room_id course_id
def AddLecture():
    #global TrainersID, trainers_count
    global RoomsID,lectures_count,LecturesID, rooms_count, total_hours
    hour = random.randint(-3, 10)
    room_id = random.randint(-3, 20)
    course_id = random.randint(-3, 40)
    inLine = "AddLecture %d %d %d" % (hour, room_id, course_id)
    outLine = "AddLecture: "
    if room_id < 0 or room_id > rooms_count-1:
        outLine += INVALID_INPUT
    elif hour < 0 or hour > total_hours-1:
        outLine += INVALID_INPUT
    elif course_id <= 0:
        outLine += INVALID_INPUT
    elif room_id not in RoomsID.keys():
        outLine += FAILURE
    elif hour in RoomsID[room_id].keys():
        outLine += FAILURE
    else:
        RoomsID[room_id][hour] = course_id
        lectures_count += 1
        if course_id not in LecturesID.keys():
            LecturesID[course_id]= 1
        else:
            LecturesID[course_id] += 1
        if hour not in ExistHours:
            ExistHours[hour] = 1
        else:
            ExistHours[hour] += 1
        outLine += SUCCESS
    return inLine, outLine

# GetCourseID hour room_id
def GetCourseID():
    global RoomsID, rooms_count, total_hours
    hour = random.randint(-2, 12)
    room_id = random.randint(-6, 20)
    inLine = "GetCourseID %d %d" % (hour, room_id)
    outLine = "GetCourseID: "
    if room_id < 0 or room_id > rooms_count-1:
        outLine += INVALID_INPUT
    elif hour < 0 or hour > total_hours-1:
        outLine += INVALID_INPUT
    elif hour not in RoomsID[room_id].keys():
        outLine += FAILURE
    else:
        outLine += "%d" % RoomsID[room_id][hour]
    return inLine, outLine

# DeleteLecture hour room_id
def DeleteLecture():
    global RoomsID,lectures_count,LecturesID, rooms_count, total_hours
    hour = random.randint(-5, 15)
    room_id = random.randint(-10, 20)
    inLine = "DeleteLecture %d %d" % (hour, room_id)
    outLine = "DeleteLecture: "
    if room_id < 0 or room_id > rooms_count-1:
        outLine += INVALID_INPUT
    elif hour < 0 or hour > total_hours-1:
        outLine += INVALID_INPUT
    elif hour not in RoomsID[room_id].keys():
        outLine += FAILURE
    else:
        course_id = RoomsID[room_id][hour]
        del RoomsID[room_id][hour]
        lectures_count -= 1
        LecturesID[course_id] -= 1
        if LecturesID[course_id] == 0:
            del LecturesID[course_id]
        ExistHours[hour] -= 1
        if ExistHours[hour] == 0:
            del ExistHours[hour]
        outLine += SUCCESS
    return inLine, outLine

# ChangeCourseID old_course_id new_course_id
def ChangeCourseID():
    global RoomsID,lectures_count,LecturesID,rooms_count
    old_course_id = random.randint(-5, 40)
    new_course_id = random.randint(-5, 40)
    inLine = "ChangeCourseID %d %d" % (old_course_id, new_course_id)
    outLine = "ChangeCourseID: "
    if old_course_id <= 0 or new_course_id <= 0:
        outLine += INVALID_INPUT
    elif old_course_id not in LecturesID.keys():
        outLine += FAILURE
    elif old_course_id == new_course_id:
        outLine += SUCCESS
    else:
        for room in RoomsID:
            for hour in RoomsID[room]:
                if RoomsID[room][hour] == old_course_id:
                    del RoomsID[room][hour]
                    RoomsID[room][hour] = new_course_id
        if new_course_id not in LecturesID.keys(): #new_course_id does not exist
            LecturesID[new_course_id] = LecturesID[old_course_id]
            del LecturesID[old_course_id]
        else:
            LecturesID[new_course_id] += LecturesID[old_course_id]
            del LecturesID[old_course_id]
        outLine += SUCCESS
    return inLine,outLine

#CalculateScheduleEfficiency
def CalculateScheduleEfficiency():
    global rooms_count,ExistHours,lectures_count
    inLine = "CalculateScheduleEfficiency"
    outLine = "CalculateScheduleEfficiency: "
    if lectures_count == 0:
        outLine += FAILURE
    else:
        outLine += "%.2f" %(lectures_count/(rooms_count*len(ExistHours.keys())))
    return inLine,outLine

#GetAllFreeRoomsByHour hour
def GetAllFreeRoomsByHour():
    global RoomsID,lectures_count,LecturesID, total_hours
    hour = random.randint(-5, 15)
    inLine = "GetAllFreeRoomsByHour %d" % (hour)
    outLine = "GetAllFreeRoomsByHour: "
    if hour < 0 or hour > total_hours-1:
        outLine += INVALID_INPUT
    else:
        empty_rooms = []
        for room in RoomsID.keys():
            if hour not in RoomsID[room]:
                empty_rooms.append(room)
        if len(empty_rooms) == 0:
            outLine += FAILURE
        else:
            outLine += SUCCESS
            outLine += "\n"
            for i in empty_rooms:
                outLine += "%d\n" %(i)
            outLine += "--End of room list--"
    return inLine,outLine

# GetAllLectureByCourse course_id
def GetAllLecturesByCourse():
    global RoomsID,lectures_count,LecturesID,ExistHours
    course_id = random.randint(-5, 40)
    inLine = "GetAllLecturesByCourse %d" % (course_id)
    outLine = "GetAllLecturesByCourse: "
    if course_id <= 0:
        outLine += INVALID_INPUT
    elif course_id not in LecturesID.keys():
        outLine += FAILURE
    else:
        outLine += SUCCESS
        outLine += "\nHour\t||\tRoom\n"
        for hour in ExistHours:
            for room in RoomsID.keys():
                if hour in RoomsID[room]:
                    if RoomsID[room][hour] == course_id:
                        outLine += "%d\t||\t%d\n" %(hour, room)
        outLine += "--End of lecture list--"
    return inLine,outLine

def main():
    if len(sys.argv) < 3:
        print "Usage %s <lines>" % sys.argv[0]
        exit(0)
    lines = int(sys.argv[1])
    infname = "%s.in" % sys.argv[2]
    outfname = "%s.out" % sys.argv[2]
    functions = [AddLecture, GetCourseID, DeleteLecture, ChangeCourseID, CalculateScheduleEfficiency, GetAllFreeRoomsByHour, GetAllLecturesByCourse]
    with open(infname, 'wb') as infhandler:
        with open(outfname, 'wb') as outfhandler:
            inLine, outLine = initline()
            infhandler.write(inLine + "\n")
            outfhandler.write(outLine + "\n")
            while lines > 0:
                f = random.randint(0, len(functions)-1)
                func = functions[f]
                inLine, outLine = func()
                if inLine is not "":
                    infhandler.write(inLine + "\n")
                    outfhandler.write(outLine + "\n")
                    lines -= 1
            infhandler.write("Quit\n")
            outfhandler.write("quit done.\n")


main()
