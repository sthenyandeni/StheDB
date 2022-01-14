# StheDB

#### The greatest database engine to ever exist  
<br/>

## Notes
- ```INTEGER``` data should be stored in an ```int64_t``` variable where its reference is stored in a ```void*``` variable.

<br/>

## TODO
- Fix: Error where first attribute on first record is a garbage value.

<br/>

## Types
### All types are nullable

1. VARCHAR (up to 255 bytes, no UNICODE)
2. INTEGER (up to 64-bit)
3. BOOLEAN

<br/>

## .sdm File

### Content (by example)

| Offset | Length | Meaning | Example |
| ------ | ------ | ------- | ------- |
| 0000 | 5 | Name of database | 0x7374686500 ("sthe\0") |
| 0005 | 1 | Number of tables | 0x02 (2) |
| 0006 | 6 | Table name | 0x757365727300 ("users\0") |
| 000c | 10 | Table Format File name | 0x75736572732e73746600 ("users.stf\0) |
| 0016 | 2 | Row Offset File ID | 0x0001 (1) |
| 0018 | 6 | Table name | 0x757365727300 ("users\0") |
| 001e | 10 | Table Format File name | 0x75736572732e73746600 ("users.stf\0) |
| 0028 | 2 | Row Offset File ID | 0x0001 (1) |

## .stf File

### Type Lookup Table

| Key | Value | Size Representation |
| --- | ----- | ------------------- |
| 0x00 | VARCHAR | Decimal as number of chars |
| 0x01 | INTEGER | Decimal as number of bytes |
| 0x02 | BOOLEAN | Default is 1 bit |

<br/>

### Content (by example)

| Offset | Length | Meaning | Example |
| ------ | ------ | ------- | ------- |
| 0000 | 1 | Number of atttributes | 0x05 (5) |
| 0001 | 1 | Length of attribute 1 name | 0x02 (2) |
| 0002 | 2 | Name of attribute 1 | 0x6964 ('id') |
| 0004 | 1 | Type of attribute 1 | 0x01 (INTEGER) |
| 0005 | 1 | Size of attribute 1 | 0x08 (8 bytes) |
| 0006 | 1 | Length of attribute 2 name | 0x0a (10) |
| 0007 | 10 | Name of attribute 2 | 0x66697273745f6e616d65 ('first_name') |
| 0011 | 1 | Type of attribute 2 | 0x00 (VARCHAR) |
| 0012 | 1 | Size of attribute 2 | 0x64 (100 chars) |
| 0013 | 1 | Length of attribute 3 name | 0x09 (9) |
| 0014 | 9 | Name of attribute 3 | 0x6c6173745f6e616d65 ('last_name') |
| 001d | 1 | Type of attribute 3 | 0x00 (VARCHAR) |
| 001e | 1 | Size of attribute 3 | 0x64 (100 chars) |
| 001f | 1 | Length of attribute 4 name | 0x0d (13) |
| 0020 | 13 | Name of attribute 4 | 0x656d61696c5f61646472657373 ('email_address') |
| 002d | 1 | Type of attribute 4 | 0x00 (VARCHAR) |
| 002e | 1 | Size of attribute 4 | 0xff (255 chars) |
| 002f | 1 | Length of attribute 5 name | 0x05 (5) |
| 0030 | 5 | Name of attribute 5 | 0x61646d696e ('admin') |
| 0035 | 1 | Type of attribute 5 | 0x02 (BOOLEAN) |
| 0036 | 1 | Size of attribute 5 | 0x01 (1 bit, default) |

<br />

## .sro File

### Content (by example)

There is a 64 byte header
Values are big-endian

| Offset | Length | Meaning | Example |
| ------ | ------ | ------- | ------- |
| START HEADER |
| 0000 | 2 | Offset File ID | 0x0001 (1) |
| 0002 | 2 | Row Data File ID | 0x0001 (1) |
| 0004 | 60 | Padding | 0x000000000000000000000000000000000000000000000000000000000000<br/>000000000000000000000000000000000000000000000000000000000000
| END HEADER |
| START CONTENT |
| 0040 | 8 | Offset of row 1 attribute 1 | 0x4000000000000000 (64) |
| 0048 | 8 | Offset of row 1 attriubte 2 | 0x4800000000000000 (72) |
| 0050 | 8 | Offset of row 1 attribute 3 | 0x7b03000000000000 (891) |
| 0058 | 8 | Offset of row 1 attribute 4 | 0xac00000000000000 (172) |
| 0060 | 8 | Offset of row 1 attribute 5 | 0x0f02000000000000 (527) |
| 0068 | 8 | Offset of row 2 attribute 1 | 0x1002000000000000 (528) |
| 0070 | 8 | Offset of row 2 attribute 2 | 0xab01000000000000 (427) |
| 0078 | 8 | Offset of row 2 attribute 3 | 0x1703000000000000 (791) |
| 0080 | 8 | Offset of row 2 attribute 4 | 0x1802000000000000 (536) |
| 0088 | 8 | Offset of row 2 attribute 5 | 0xdf03000000000000 (991) |



## .srd File

### Content (by example)

There is a 64 byte header

| Offset | Length | Meaning | Example |
| ------ | ------ | ------- | ------- |
| START HEADER |
| 0000 | 2 | File ID | 0x0001 (1) |
| 0002 | 2 | Previous Data File ID | 0x0000 (0) |
| 0004 | 2 | Next Data File ID | 0x0000 (0) |
| 0006 | 58 | Padding | 0x0000000000000000000000000000000000000000000000000000000000<br/>0000000000000000000000000000000000000000000000000000000000 |
| END HEADER |
| START CONTENT |
| 0040 | 8 | id attribute for row 1 | 0x0000000000000001 (1) |
| 0048 | 100 | first_name for row 1 | 0x0000000000000000000000000000000000000000000000000000000000<br/>000000000000000000000000000000000000000000000000000000000000<br/>000000000000000000000000000000000000000000000000000000000000<br/>0053697468656d6269736f (Sithembiso) |
| 00ac | 255 | email_address for row 1 | 0x0000000000000000000000000000000000000000000000000000000000<br/>0000000000000000000000000000000000000000000000000000000000<br/>0000000000000000000000000000000000000000000000000000000000<br/>0000000000000000000000000000000000000000000000000000000000<br/>0000000000000000000000000000000000000000000000000000000000<br/>0000000000000000000000000000000000000000000000000000000000000000000000000000000<br/>000000000000000000000000000000000000000000000000000000000000<br/>00000000000000000000000000000000000006e79616e64656e697374686<br/>540676d61696c2e636f6d (nyandenisthe@gmail.com)|
| 01ab | 100 | first_name for row 2 | 0x00000000000000000000000000000000000000000000000000000000000<br/>000000000000000000000000000000000000000000000000000000000000<br/>000000000000000000000000000000000000000000000000000000000000<br/>00000000053616d75656c (Samuel) |
| 020f | 1 | admin for row 1 | 0x01 (true) |
| 0210 | 8 | id attribute for row 2 | 0x000000000000000b (11) |
| 0218 | 255 | email_address for row 2 | 0x00000000000000000000000000000000000000000000000000000000000<br/>00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000<br/>00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000<br/>00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000<br/>0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000073616d756<br/>56c2e6d636461746162617365407374686564622e636f6d (samuel.mcdatabase@sthedb.com) |
| 0317 | 100 | last_name for row 2 | 0x00000000000000000000000000000000000000000000000000000000000<br/>000000000000000000000000000000000000000000000000000000000000<br/>000000000000000000000000000000000000000000000000000000000000<br/>04d634461746162617365 (McDatabase) |
| 037b | 100 | last_name for row 1 | 0x00000000000000000000000000000000000000000000000000000000000<br/>000000000000000000000000000000000000000000000000000000000000<br/>000000000000000000000000000000000000000000000000000000000000<br/>000004e79616e64656e69 (Nyandeni) |
| 03df | 1 | admin for row 2 | 0x00 (false)