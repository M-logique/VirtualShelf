# Base image for building
FROM ubuntu:22.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive
RUN apt update && apt install -y \
    cmake \
    g++ \
    make \
    golang \
    mingw-w64 \
    sqlite3 \
    libsqlite3-dev \
    git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .
COPY ./libtui.lib /app/libtui.lib

RUN cmake -S . -B build -DPLATFORM=windows -DLIBTUI_PATH=/app/libtui.lib
RUN cmake --build build

RUN mkdir -p /output && cp /app/build/VirtualShelf /output/

FROM alpine AS final

WORKDIR /output

COPY --from=builder /output/ /output/

CMD ["true"]
