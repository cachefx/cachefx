FROM python:3.9

RUN apt update

# install python packages
RUN pip3 install pandas

COPY ./cachefx /workdir/cachefx
COPY ./Docker/collectData.py /scripts/collectData.py


# Set the working directory (to be used when mounting files from the host).
WORKDIR /workdir
VOLUME /workdir

ENTRYPOINT ["python3", "/scripts/collectData.py"]
# ENTRYPOINT ["bash"]