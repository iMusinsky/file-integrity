FROM ubuntu:18.04 AS dev

RUN apt-get update \
  && apt-get install -y apt-utils

RUN apt-get update \
  && apt-get install -y \
  build-essential \
  gcc \
  gcc-multilib \
  gdb \
  git \
  git-svn \
  language-pack-ru \
  make \
  mc \
  && rm -rf /var/lib/apt/lists/*

WORKDIR /data

EXPOSE 22

ENTRYPOINT	/bin/bash
