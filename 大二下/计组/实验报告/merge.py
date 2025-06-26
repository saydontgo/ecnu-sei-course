import os
from PyPDF2 import PdfMerger

def merge_pdfs_in_directory(directory_path, output_path='merged.pdf'):
    # 获取目录下所有 PDF 文件（按文件名排序）
    pdf_files = sorted([
        f for f in os.listdir(directory_path)
        if f.lower().endswith('.pdf')
    ])

    if not pdf_files:
        print("该目录下没有 PDF 文件。")
        return

    merger = PdfMerger()

    for pdf in pdf_files:
        full_path = os.path.join(directory_path, pdf)
        print(f"添加文件：{pdf}")
        merger.append(full_path)

    merger.write(output_path)
    merger.close()
    print(f"合并完成，输出文件：{output_path}")

# 示例使用方式：
if __name__ == "__main__":
    folder = "./"  # 例如："./pdfs"
    output_file = "1023510477_张建夫_计组实验报告.pdf"
    merge_pdfs_in_directory(folder, output_file)