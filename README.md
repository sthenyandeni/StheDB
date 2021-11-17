# StheDB

#### The greatest database engine to ever exist  
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
| 0000 | 1 | Number of tables | 0x01 (1) |
| 0001 | 6 | Table name | 0x757365727300 ("users\0") |
| 0007 | 10 | Table Format File name | 0x75736572732e73746600 ("users.stf\0) |

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
| 0002 | 1 | Length of attribute 2 name | 0x0a (10) |
| 0003 | 1 | Length of attribute 3 name | 0x09 (9) |
| 0004 | 1 | Length of attribute 4 name | 0x0d (13) |
| 0005 | 1 | Length of attribute 5 name | 0x05 (5) |
| 0006 | 2 | Name of attribute 1 | 0x6964 ('id') |
| 0008 | 10 | Name of attribute 2 | 0x66697273745f6e616d65 ('first_name') |
| 0012 | 9 | Name of attribute 3 | 0x6c6173745f6e616d65 ('last_name') |
| 001b | 13 | Name of attribute 4 | 0x656d61696c5f61646472657373 ('email_address') |
| 002e | 5 | Name of attribute 5 | 0x61646d696e ('admin') |
| 0033 | 1 | Type of attribute 1 | 0x01 (INTEGER) |
| 0034 | 1 | Type of attribute 2 | 0x00 (VARCHAR) |
| 0035 | 1 | Type of attribute 3 | 0x00 (VARCHAR) |
| 0036 | 1 | Type of attribute 4 | 0x00 (VARCHAR) |
| 0037 | 1 | Type of attribute 5 | 0x02 (BOOLEAN) |
| 0038 | 1 | Size of attribute 1 | 0x08 (8 bytes) |
| 0039 | 1 | Size of attribute 2 | 0x64 (100 chars) |
| 003a | 1 | Size of attribute 3 | 0x64 (100 chars) |
| 003b | 1 | Size of attribute 4 | 0xff (255 chars) |
| 003c | 1 | Size of attribute 5 | 0x01 (1 bit, default) |