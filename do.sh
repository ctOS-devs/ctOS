#!/bin/bash

shopt -s expand_aliases
alias rt="$PWD/rtracker"


help() {
# echo "Available commands:"
cat << EOF
Usage: ./do.sh [command] (sub_command)

Main commands:
  * help  - Get out help.
  * get_requirements - Get requirements for work.
  * build_img - Build .img file.
  * make_iso - Create .iso file.
  * burn_iso - Burn .iso to some device.
  * run - Run VM with ctOS.
  * run_iso - Run .iso in VM.
  * run_tty - Run VM with ctOS in terminal.
  * all - Build all, then run ctOS in VM.

Also available commands:
  * rtracker_download - Download run tracker.
  * rootfs_download - Download rootfs.
  * init_img - Init .img file.
  * make_rootfs - Make full rootfs.
EOF
}


# ---------------- FUNCTIONS -----------------
require_root() {
if [ "$EUID" -ne 0 ]; then
	echo "Please run this script with sudo."
	exit 1
fi
}
# ------------------ END ---------------------


# ------------- DEFINE COMMANDS --------------
get_requirements() {
rtracker_download

echo 
rt 'Updating repos..' \
	%% sudo apt update
rt 'Installing packages..' \
	%% sudo apt install --yes qemu-system-x86 extlinux syslinux-utils musl-tools gcc genisoimage python3-pip
rt 'Installing python packages...' \
	%% python3 -m pip install nuitka simple_term_menu
echo ''
echo '-----------'
echo 'DONE!'
echo '-----------'
}

rtracker_download() {
# Define variables
LOCAL_BINARY="rtracker"
REMOTE_URL="https://gitea.del.pw/justuser-31/run_tracker/releases/download/latest/rtracker_x86"
TEMP_FILE="rtracker_temp"

# Function to download the latest binary
download_latest() {
    curl -L -o "$TEMP_FILE" "$REMOTE_URL"
    if [ $? -eq 0 ]; then
        mv "$TEMP_FILE" "$LOCAL_BINARY"
        chmod +x "$LOCAL_BINARY"
    else
        echo "[RT DOWN] Failed to download rtracker."
        exit 1
    fi
}

# Check if the local binary exists
if [ -f "$LOCAL_BINARY" ]; then
    # Get the local file hash
    LOCAL_HASH=$(sha256sum "$LOCAL_BINARY" | awk '{ print $1 }')

    # Check if the remote version is accessible
    if curl --output /dev/null --silent --head --fail "$REMOTE_URL"; then
        # Get the remote file hash
        REMOTE_HASH=$(curl -s "$REMOTE_URL" | sha256sum | awk '{ print $1 }')

        # Compare hashes
        if [ "$LOCAL_HASH" != "$REMOTE_HASH" ]; then
            #echo "A newer version is available."
            download_latest
        fi
    fi
else
    download_latest
fi
}

rootfs_download() {
# Define variables
LOCAL_ARCHIVE="rootfs-main.tar.gz"
REPO_URL="https://api.github.com/repos/ctOS-devs/rootfs/releases/latest"
VERSION_FILE="rootfs_version.txt"

# Function to download the latest release
download_latest() {
    curl -L -o "$LOCAL_ARCHIVE" "$DOWNLOAD_URL"
    if [ $? -eq 0 ]; then
    	if [ ! -d rootfs ]; then
    		mkdir rootfs
    	fi
        rm -rf rootfs/*
        tar -xf rootfs-main.tar.gz -C rootfs/
        EXTRACTED_DIR=$(find "rootfs" -mindepth 1 -maxdepth 1 -type d -name "ctOS-devs-rootfs-*")
        mv $EXTRACTED_DIR/* rootfs/
        rm -r $EXTRACTED_DIR rootfs-main.tar.gz
    else
        echo "Failed to download the latest release."
        return 1
    fi
}

# Check if the version file exists
if [ -f "$VERSION_FILE" ]; then
    LOCAL_VERSION=$(cat "$VERSION_FILE")

    # Check if the remote version is accessible
    if curl --output /dev/null --silent --head --fail "$REPO_URL"; then
        # Get the latest release information
        LATEST_INFO=$(curl -s "$REPO_URL")

        # Extract the latest version and download URL without jq
        LATEST_VERSION=$(echo "$LATEST_INFO" | grep -oP '"tag_name": "\K(.*?)(?=")')
        DOWNLOAD_URL=$(echo "$LATEST_INFO" | grep -oP '"tarball_url": "\K(.*?)(?=")')

        # Compare versions
        if [ "$LOCAL_VERSION" != "$LATEST_VERSION" ]; then
            download_latest
            echo $LATEST_VERSION > $VERSION_FILE
        fi
    fi
else
	LOCAL_VERSION=""
    # Check if the remote version is accessible
    if curl --output /dev/null --silent --head --fail "$REPO_URL"; then
        # Get the latest release information
        LATEST_INFO=$(curl -s "$REPO_URL")
        
        # Extract the latest version and download URL
        LATEST_VERSION=$(echo "$LATEST_INFO" | grep -oP '"tag_name": "\K(.*?)(?=")')
        DOWNLOAD_URL=$(echo "$LATEST_INFO" | grep -oP '"tarball_url": "\K(.*?)(?=")')
        
        download_latest
        echo $LATEST_VERSION > $VERSION_FILE
    else
    	# Error - can't download
        return 1
    fi
fi
}

init_img() {
require_root

rt "[INIT]: UMOUNT boot.img..." \
	%t umount mounted/
rt "[INIT]: RM boot.img..." \
	%t rm boot.img
rt "[INIT]: CREATE NEW boot.img..." \
	%% truncate -s 1GB boot.img
rt "[INIT]: CHMOD 777 boot.img..." \
	%% chmod 777 boot.img
rt "[INIT]: CREATE NEW mounted dir" \
	%t mkdir mounted
rt "[INIT]: CREATE FILESYSTEM..." \
	%% mkfs boot.img
rt "[INIT]: MOUNT boot.img TO mounted/ ..." \
	%% mount boot.img mounted/
rt "[INIT]: INSTALLING SYSLINUX BOOTLOADER..." \
	%% extlinux --install mounted/
}

make_rootfs() {
require_root

rt "[BUILD]: RM old rootfs..." \
	%t rm -rf rootfs_full
rt "[BUILD]: MK rootfs_full..."\
	%% mkdir -p rootfs_full/progs
rt "[BUILD]: CP rootfs..." \
	%% cp -r rootfs/* rootfs_full
rt "[BUILD]: CP progs..." \
	%% cp -r progs/binary_files/* rootfs_full/progs/
rt "[BUILD]: CP additional files..." \
	%% cp -r additional_files/*/* rootfs_full/
rt "[BUILD]: CP packages into rootfs_full..." \
	%% cp -rf packages rootfs_full/packages
rt "[BUILD]: INSTALL packages..." \
	%% chroot ./rootfs_full packages/prepare_rootfs.sh
}

build_img() {
require_root

rt "[BUILD]: MOUNT boot.img TO mounted/..." \
	%t mount boot.img mounted/
rt "[BUILD]: RM old files" \
	%% find mounted/ ! -name 'mounted' ! -name 'lost+found' ! -name 'ldlinux.sys' ! -name 'ldlinux.c32' -delete
make_rootfs
rt "[BUILD]: COPY rootfs in drive..." \
	%% cp -r rootfs_full/* mounted/
rt "[BUILD]: COPY SYSLINUX TO mounted/..." \
	%% cp -r syslinux mounted/
rt "[BUILD]: FIX PERMISSIONS..." \
	%% chmod -R 755 mounted/syslinux/ && \
		chmod 644 mounted/syslinux/syslinux.cfg
rt "[BUILD]: ENSURE SYSLINUX CONFIG READABLE..." \
	%% chmod 644 mounted/syslinux/*.cfg 2>/dev/null || true
# Это решает ПОСТОЯННУЮ проблему "No configuration file found"
# Возникает из-за недозаписи файлов, теперь мы ждём пока всё выполнится
# Если в другой части возникает "плавающая ошибка" - пробуйте это
rt "[BUILD]: SYNC filesystem..." \
	%% sync
rt "[BUILD]: UNMOUNT boot.img..." \
	%% umount mounted/
rt "[BUILD]: FINAL SYNC..." \
	%% sync
}

make_iso() {
require_root

rt "[BUILD]: COPY kernel to boot..." \
	%% cp rootfs/bzImage isofiles/boot/bzImage
rt "[BUILD]: MAKE full rootfs..." \
	%t make_rootfs
rt "[BUILD]: RM old rootfs..." \
	%t rm -r isofiles/rootfs
rt "[BUILD]: MKDIR rootfs..." \
	%% mkdir isofiles/rootfs
rt "[BUILD]: COPY rootfs..." \
	%% cp -r rootfs_full/* isofiles/rootfs/
rt "[BUILD]: COPY init script to rootfs..." \
	%% cp isofiles/init rootfs/init

cd rootfs
rt "[BUILD]: GENERATE initrd.img..." \
	%% 'find . | cpio -o -H newc | gzip -c > ../isofiles/boot/initrd.img'
cd ../

rt "[BUILD]: RM init script in rootfs..." \
	%% rm rootfs/init
rt "[BUILD]: GENERATE iso..." \
	%% grub-mkrescue -o ctOS.iso isofiles/
}

burn_iso() {
require_root

lsblk
echo "------------------"
echo "To what of this devices you want burn iso image?"
echo "------------------"

read -p "/dev/... : " dev_path

echo "------------------"
echo "Your choice: %s, are you sure?" $dev_path
echo "------------------"

read -p "(y/n): " confirm

if [ $confirm != "y" ]; then
	echo "EXIT!!!"
	exit 0
fi

echo "--- Burning... ---"
umount $dev_path*
dd if=ctOS.iso of=$dev_path bs=4M status=progress
echo "------------------"
}

run() {
rt "[RUN]: RUNNING ctOS ON QEMU..." \
	%o qemu-system-x86_64 -hda boot.img
}

run_iso() {
rt "[RUN]: RUNNING ctOS ON QEMU..." \
	%o qemu-system-x86_64 -cdrom ctOS.iso -m 1024M
}

run_tty() {
qemu-system-x86_64 -kernel rootfs_full/bzImage -append "root=/dev/sda console=ttyS0" -hda boot.img -nographic -m 1024M
}

all() {
# Инициализация и обновление модулей
git submodule update --init --recursive --remote

rtracker_download
rootfs_download
init_img
build_img
run
}
# ------------------ END ---------------------


# Execute the requested command
if declare -F "$1" > /dev/null; then
    "$1"
else
    help
fi

