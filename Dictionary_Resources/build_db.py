import sqlite3
from tqdm import tqdm
import sys
from lxml import etree

def build(jmdict_path, kanjidic_path, db_path):
    con = sqlite3.connect(db_path)
    cur = con.cursor()
    cur.executescript("""
        DROP TABLE IF EXISTS word;
        DROP TABLE IF EXISTS word_form;
        DROP TABLE IF EXISTS kanji;

        CREATE TABLE word (
            ent_seq INTEGER PRIMARY KEY,
            readings TEXT,     
            kanji    TEXT,    
            senses   TEXT    
        );

        CREATE TABLE word_form (
            form    TEXT,
            ent_seq INTEGER
        );
        CREATE INDEX idx_form ON word_form(form);

        CREATE TABLE kanji (
            literal      TEXT PRIMARY KEY,
            stroke_count INTEGER,
            grade        INTEGER,
            on_readings  TEXT,
            kun_readings TEXT,
            meanings     TEXT
        );
    """)

    ctx = etree.iterparse(jmdict_path, tag="entry",
                          resolve_entities=True, load_dtd=True)
    for _, entry in tqdm(ctx):
        ent_seq = int(entry.findtext("ent_seq"))
        kanji    = [k.text for k in entry.findall("k_ele/keb")]
        readings = [r.text for r in entry.findall("r_ele/reb")]

        sense_lines = []
        for sense in entry.findall("sense"):
            pos    = [p.text for p in sense.findall("pos")]
            gloss  = [g.text for g in sense.findall("gloss")]
            prefix = f"[{', '.join(pos)}] " if pos else ""
            sense_lines.append(prefix + "; ".join(gloss))

        cur.execute(
            "INSERT INTO word VALUES (?,?,?,?)",
            (ent_seq, ";".join(readings), ";".join(kanji),
             "\n".join(sense_lines)))

        for form in set(kanji + readings):
            cur.execute("INSERT INTO word_form VALUES (?,?)", (form, ent_seq))

        entry.clear()  
    con.commit()

    ctx = etree.iterparse(kanjidic_path, tag="character", resolve_entities=False, load_dtd=False)

    for _, ch in tqdm(ctx):
        literal = ch.findtext("literal")
        stroke  = ch.findtext("misc/stroke_count")
        grade   = ch.findtext("misc/grade")
        on  = [r.text for r in ch.findall("reading_meaning/rmgroup/reading[@r_type='ja_on']")]
        kun = [r.text for r in ch.findall("reading_meaning/rmgroup/reading[@r_type='ja_kun']")]
        # meanings with no m_lang attribute are English
        mean = [m.text for m in ch.findall("reading_meaning/rmgroup/meaning")
                if m.get("m_lang") is None]

        cur.execute(
            "INSERT OR REPLACE INTO kanji VALUES (?,?,?,?,?,?)",
            (literal,
             int(stroke) if stroke else None,
             int(grade) if grade else None,
             ";".join(on), ";".join(kun), ";".join(mean)))
        ch.clear()
    con.commit()
    con.close()

if __name__ == "__main__":
    build(sys.argv[1], sys.argv[2], sys.argv[3])
