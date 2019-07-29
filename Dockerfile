# use ubuntu environment as base environment
FROM amytabb/docker_ubuntu16_essentials
COPY PostProcess_EpiScale_Feb2017 /PostProcess_EpiScale_Feb2017
WORKDIR /PostProcess_EpiScale_Feb2017
#compile and run
RUN make
CMD ["./cell"]

