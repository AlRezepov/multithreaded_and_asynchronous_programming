FROM ubuntu:latest
    LABEL Name=task02 Version=0.0.1
    RUN apt-get -y update && apt-get install -y g++ nano net-tools
    WORKDIR /root/task_02
    COPY task_02.cpp .
    RUN g++ task_02.cpp -o task_02
    CMD ["./task_02"]
