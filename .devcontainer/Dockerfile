ARG DOCKER_TAG=v6.2.2
FROM espressif/idf:${DOCKER_TAG}

ENV LC_ALL=C.UTF-8
ENV LANG=C.UTF-8

RUN apt-get update -y && apt-get install udev -y

RUN echo "source /opt/esp/idf/export.sh > /dev/null 2>&1" >> ~/.bashrc

RUN chmod +x /opt/esp/tools/idf-cli/1.0.8/idf.py && \
    sed -i 's|CMD=\"/bin/bash\\"|CMD=\"/bin/bash\\"|g' /opt/esp/entrypoint.sh

ENTRYPOINT [ "/opt/esp/entrypoint.sh" ]

CMD ["/bin/bash", "-c"] 