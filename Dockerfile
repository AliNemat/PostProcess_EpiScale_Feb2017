FROM amytabb/docker_ubuntu16_essentials
COPY PostProcess_EpiScale_Feb2017 /PostProcess_EpiScale_Feb2017
WORKDIR /PostProcess_EpiScale_Feb2017
RUN make
CMD ["./cell"]

